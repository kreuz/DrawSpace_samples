
#ifndef _DSAPPCLIENT_H_
#define _DSAPPCLIENT_H_

#include <dsapp.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class dsAppClient : public DrawSpace::App
{
protected:

    static dsAppClient*                                                 m_instance;


    DrawSpace::Core::SceneNodeGraph                                     m_scenenodegraph;


    DrawSpace::IntermediatePass*                                        m_texturepass;
    DrawSpace::FinalPass*                                               m_finalpass;


    DrawSpace::Utils::TimeManager                                       m_timer;

    bool                                                                m_mouselb;
    bool                                                                m_mouserb;

    DrawSpace::Gui::TextWidget*                                         m_fpstext_widget;

    DrawSpace::Interface::FontImport*                                   m_font_import;
    DrawSpace::Core::Font*                                              m_font;

    DrawSpace::Dynamics::CameraPoint*                                   m_camera;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>*       m_camera_node;

    DrawSpace::Dynamics::CameraPoint*                                   m_camera_2;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>*       m_camera2_node;


    DrawSpace::Core::FPSMovement                                        m_fpsmove;
    DrawSpace::Core::SceneNode<DrawSpace::Core::FPSMovement>*           m_fpsmove_node;

    DrawSpace::Core::LinearMovement*                                    m_linear_mvt;
    DrawSpace::Core::SceneNode<DrawSpace::Core::LinearMovement>*        m_linearmove_node;
    
    


    DrawSpace::Spacebox*                                                m_spacebox;
    DrawSpace::Core::SceneNode<DrawSpace::Spacebox>*                    m_spacebox_node;
    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*        m_spacebox_transfo_node;

    DrawSpace::Interface::MesheImport*                                  m_meshe_import;

    DrawSpace::Chunk*                                                   m_ground;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                       m_ground_node;

    DrawSpace::Dynamics::InertBody*                                     m_ground_body;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::InertBody>*         m_ground_body_node;


    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*        m_impostor_transfo_node;

    DrawSpace::Impostor*                                                m_impostor;
    DrawSpace::Core::SceneNode<DrawSpace::Impostor>*                    m_impostor_node;


    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*        m_impostor2_transfo_node;

    DrawSpace::Core::SceneNode<DrawSpace::Core::LongLatMovement>*       m_impostor2_ll_node;


    DrawSpace::Impostor*                                                m_impostor2;
    DrawSpace::Core::SceneNode<DrawSpace::Impostor>*                    m_impostor2_node;



    int                                                                 m_box_count;
    int                                                                 m_box_texture;

    DrawSpace::Dynamics::World                                          m_world;

    DrawSpace::Dynamics::Calendar*                                      m_calendar;


    dsreal                                                              m_zoom;

    DrawSpace::Image*                                                   m_image1;

    typedef struct
    {        
        DrawSpace::Chunk*                                               drawable;
        DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                   drawable_node;
        DrawSpace::Dynamics::InertBody*                                 inert_body;
        DrawSpace::Core::SceneNode<DrawSpace::Dynamics::InertBody>*     inert_body_node;

    } Box;

    std::vector<Box>                                                    m_boxes;


    dsstring                                                            m_current_camera;


    void create_box( void );

    dsAppClient( void );

public:

    ~dsAppClient( void );

    static dsAppClient* GetInstance( void )
    {
        if( m_instance == NULL )
        {
            m_instance = new dsAppClient;
        }

        DrawSpace::App::m_base_instance = m_instance;
        return m_instance;
    }

    virtual void OnRenderFrame( void );
    virtual bool OnIdleAppInit( void );
    virtual void OnAppInit( void );
    virtual void OnClose( void );
    virtual void OnKeyPress( long p_key ) ;
    virtual void OnEndKeyPress( long p_key );
    virtual void OnKeyPulse( long p_key );
    virtual void OnMouseMove( long p_xm, long p_ym, long p_dx, long p_dy );
    virtual void OnMouseLeftButtonDown( long p_xm, long p_ym );
    virtual void OnMouseLeftButtonUp( long p_xm, long p_ym );
    virtual void OnMouseRightButtonDown( long p_xm, long p_ym );
    virtual void OnMouseRightButtonUp( long p_xm, long p_ym );
    virtual void OnAppEvent( WPARAM p_wParam, LPARAM p_lParam );
};

#endif

