#include "dsappclient.h"

using namespace DrawSpace;
using namespace DrawSpace::Interface;
using namespace DrawSpace::Core;
using namespace DrawSpace::Utils;
using namespace DrawSpace::Gui;

dsAppClient* dsAppClient::m_instance = NULL;


dsAppClient::dsAppClient( void ) : m_mouselb( false ), m_mouserb( false )
{    
    _INIT_LOGGER( "loggpunoise3.conf" )  
    m_w_title = "gpu perlin noise test 3";
}

dsAppClient::~dsAppClient( void )
{

}

void dsAppClient::OnRenderFrame( void )
{


    DrawSpace::Interface::Renderer* renderer = DrawSpace::Core::SingletonPlugin<DrawSpace::Interface::Renderer>::GetInstance()->m_interface;

    m_scenenodegraph.ComputeTransformations( m_timer );



    m_texturepass->GetRenderingQueue()->Draw();
    m_finalpass->GetRenderingQueue()->Draw();


    renderer->DrawText( 255, 0, 0, 10, 20, "%d fps", m_timer.GetFPS() );

    renderer->FlipScreen();

    m_timer.Update();
    if( m_timer.IsReady() )
    {
    }
}

bool dsAppClient::OnIdleAppInit( void )
{
    DrawSpace::Interface::Renderer* renderer = DrawSpace::Core::SingletonPlugin<DrawSpace::Interface::Renderer>::GetInstance()->m_interface;
    renderer->SetRenderState( &DrawSpace::Core::RenderState( DrawSpace::Core::RenderState::SETCULLING, "cw" ) );


    m_texturepass = _DRAWSPACE_NEW_( IntermediatePass, IntermediatePass( "texture_pass" ) );
    m_texturepass->SetTargetDimsFromRenderer( false );
    m_texturepass->SetTargetDims( 256, 256 );
    m_texturepass->Initialize();
    m_texturepass->CreateViewportQuad();
    
    m_texturepass->GetViewportQuad()->SetFx( _DRAWSPACE_NEW_( Fx, Fx ) );
    m_texturepass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "noise3.vsh", false ) ) );
    m_texturepass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "noise3.psh", false ) ) );
    m_texturepass->GetViewportQuad()->GetFx()->GetShader( 0 )->LoadFromFile();
    m_texturepass->GetViewportQuad()->GetFx()->GetShader( 1 )->LoadFromFile();
    m_texturepass->GetViewportQuad()->GetFx()->AddRenderStateIn( DrawSpace::Core::RenderState( DrawSpace::Core::RenderState::SETTEXTUREFILTERTYPE, "none" ) );
    m_texturepass->GetViewportQuad()->GetFx()->AddRenderStateOut( DrawSpace::Core::RenderState( DrawSpace::Core::RenderState::SETTEXTUREFILTERTYPE, "none" ) );



    m_perlinnoiseperm_texture = new Texture();    
    m_perlinnoiseperm_texture->SetFormat( 256, 1, 4 );
    m_perlinnoiseperm_texture->SetPurpose( Texture::PURPOSE_FLOAT );


    m_perlinnoisegrad_texture = new Texture();
    m_perlinnoisegrad_texture->SetFormat( 16, 1, 4 );
    m_perlinnoisegrad_texture->SetPurpose( Texture::PURPOSE_COLOR );



    m_texturepass->GetViewportQuad()->SetTexture( m_perlinnoiseperm_texture, 0 );
    m_texturepass->GetViewportQuad()->SetTexture( m_perlinnoisegrad_texture, 1 );


    
    m_finalpass = _DRAWSPACE_NEW_( FinalPass, FinalPass( "final_pass" ) );
    m_finalpass->Initialize();
    m_finalpass->CreateViewportQuad();
    m_finalpass->GetViewportQuad()->SetFx( _DRAWSPACE_NEW_( Fx, Fx ) );
    m_finalpass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "texture.vsh", false ) ) );
    m_finalpass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "texture.psh", false ) ) );
    m_finalpass->GetViewportQuad()->GetFx()->GetShader( 0 )->LoadFromFile();
    m_finalpass->GetViewportQuad()->GetFx()->GetShader( 1 )->LoadFromFile();
    m_finalpass->GetViewportQuad()->GetFx()->AddRenderStateIn( DrawSpace::Core::RenderState( DrawSpace::Core::RenderState::SETTEXTUREFILTERTYPE, "none" ) );
    m_finalpass->GetViewportQuad()->GetFx()->AddRenderStateOut( DrawSpace::Core::RenderState( DrawSpace::Core::RenderState::SETTEXTUREFILTERTYPE, "none" ) );
    

    m_finalpass->GetViewportQuad()->SetTexture( m_texturepass->GetTargetTexture(), 0 );


       




    /////////////////////////////////////////////////////////////////




    m_finalpass->GetRenderingQueue()->UpdateOutputQueue();
    m_texturepass->GetRenderingQueue()->UpdateOutputQueue();

    m_perlinnoiseperm_texture->AllocTextureContent();
    m_permtexture_content = m_perlinnoiseperm_texture->GetTextureContentPtr();

    m_perlinnoisegrad_texture->AllocTextureContent();
    m_gradtexture_content = m_perlinnoisegrad_texture->GetTextureContentPtr();



    std::default_random_engine generator;
    std::uniform_real_distribution<double> rf( -0.5, 0.5 );
    std::uniform_int_distribution<int> ri( 0, 255 );
    generator.seed( 144539 );

    float perm[256];
    int i, j;
    float k;

    for( i = 0; i < 256; i++ )
    {
        perm[i] = float(i) / 256.0;
    }
    
	while( --i )
	{
        j = ri( generator );

        k = perm[i];
        perm[i] = perm[j];
        perm[j] = k;
	}

    
    float* float_ptr;
    
    float_ptr = (float*)m_permtexture_content;        
    for( long i = 0; i < 256; i++ )
    {
       *float_ptr = perm[i];
       float_ptr++;
    }


    unsigned char* color_ptr = (unsigned char*)m_gradtexture_content;

    *color_ptr = 255; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;



    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;



    *color_ptr = 128; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 128; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;


    *color_ptr = 255; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 255; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;

    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 0; color_ptr++;


    m_perlinnoiseperm_texture->UpdateTextureContent();
    m_perlinnoisegrad_texture->UpdateTextureContent();



    return true;
}

void dsAppClient::OnAppInit( void )
{

}

void dsAppClient::OnClose( void )
{
}

void dsAppClient::OnKeyPress( long p_key ) 
{
    switch( p_key )
    {
        case 'Q':

            break;

        case 'W':

            break;

        case VK_F3:

            break;

    }

}

void dsAppClient::OnEndKeyPress( long p_key )
{
    switch( p_key )
    {
        case 'Q':
        case 'W':

            break;      
    }

}

void dsAppClient::OnKeyPulse( long p_key )
{
    switch( p_key )
    {
        case VK_F1:

            break;

        case VK_F2:
            break;
    }
}

void dsAppClient::OnMouseMove( long p_xm, long p_ym, long p_dx, long p_dy )
{
    if( m_mouserb )
    {
    }

    else
    {
    }
}

void dsAppClient::OnMouseLeftButtonDown( long p_xm, long p_ym )
{
    m_mouselb = true;
}

void dsAppClient::OnMouseLeftButtonUp( long p_xm, long p_ym )
{
    m_mouselb = false;
}

void dsAppClient::OnMouseRightButtonDown( long p_xm, long p_ym )
{
    m_mouserb = true;
}

void dsAppClient::OnMouseRightButtonUp( long p_xm, long p_ym )
{
    m_mouserb = false;
}

void dsAppClient::OnAppEvent( WPARAM p_wParam, LPARAM p_lParam )
{

}
