#include "dsappclient.h"

using namespace DrawSpace;
using namespace DrawSpace::Interface;
using namespace DrawSpace::Core;
using namespace DrawSpace::Utils;
using namespace DrawSpace::Gui;

dsAppClient* dsAppClient::m_instance = NULL;



dsAppClient::dsAppClient( void ) : m_mouselb( false ), m_mouserb( false )
{    
    _INIT_LOGGER( "lognoise.conf" )  
    m_w_title = "noise test";
}

dsAppClient::~dsAppClient( void )
{

}

void dsAppClient::OnRenderFrame( void )
{


    DrawSpace::Interface::Renderer* renderer = DrawSpace::Core::SingletonPlugin<DrawSpace::Interface::Renderer>::GetInstance()->m_interface;

    m_scenenodegraph.ComputeTransformations( m_timer );

    /*
    unsigned char* color_ptr = (unsigned char*)m_texture_content;

    *color_ptr = 0; color_ptr++;
    *color_ptr = 128; color_ptr++;
    *color_ptr = 0; color_ptr++;
    *color_ptr = 255; color_ptr++;
    
    */

    float* float_ptr = (float*)m_texture_content;
    *float_ptr = 0.25f; float_ptr++;
    *float_ptr = 0.5f; float_ptr++;
    *float_ptr = 0.75f; float_ptr++;



    m_perlinnoise_texture->UpdateTextureContent();


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
   
    m_finalpass = _DRAWSPACE_NEW_( FinalPass, FinalPass( "final_pass" ) );
    m_finalpass->Initialize();
    m_finalpass->CreateViewportQuad();
    m_finalpass->GetViewportQuad()->SetFx( _DRAWSPACE_NEW_( Fx, Fx ) );
    m_finalpass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "noise.vsh", false ) ) );
    m_finalpass->GetViewportQuad()->GetFx()->AddShader( _DRAWSPACE_NEW_( Shader, Shader( "noise.psh", false ) ) );
    m_finalpass->GetViewportQuad()->GetFx()->GetShader( 0 )->LoadFromFile();
    m_finalpass->GetViewportQuad()->GetFx()->GetShader( 1 )->LoadFromFile();
    

    //m_finalpass->GetViewportQuad()->SetTexture( m_fogblendpass->GetTargetTexture(), 0 );
        

    m_perlinnoise_texture = new Texture();
    m_perlinnoise_texture->SetFormat( 256, 256, 4 );
    m_perlinnoise_texture->SetPurpose( Texture::PURPOSE_FLOAT );

    m_finalpass->GetViewportQuad()->SetVertexTexture( m_perlinnoise_texture, 0 );

    /////////////////////////////////////////////////////////////////


    m_mouse_circularmode = true;



    m_finalpass->GetRenderingQueue()->UpdateOutputQueue();

    m_perlinnoise_texture->AllocTextureContent();
    m_texture_content = m_perlinnoise_texture->GetTextureContentPtr();



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
