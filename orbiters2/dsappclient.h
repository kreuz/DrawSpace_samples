
#ifndef _DSAPPCLIENT_H_
#define _DSAPPCLIENT_H_

#include <dsapp.h>


class MyPlanet
{
protected:

    typedef DrawSpace::Core::CallBack<MyPlanet, void, int>                              PlanetEvtCb;

    typedef DrawSpace::Core::CallBack<MyPlanet, void, DrawSpace::Core::PropertyPool*>   RunnerEvtCb;

    DrawSpace::Dynamics::World                              m_world;
    dsstring                                                m_name;
    DrawSpace::Dynamics::Orbiter*                           m_orbiter;
    DrawSpace::Planet::Body*                                m_drawable;
    PlanetEvtCb*                                            m_planet_evt_cb;

    RunnerEvtCb*                                            m_runner_evt_cb;

    dsreal                                                  m_ray;

    bool                                                    m_collision_state;

    std::vector<DrawSpace::Dynamics::InertBody*>            m_attached_bodies;
    DrawSpace::Dynamics::InertBody*                         m_player_body;

    bool                                                    m_player_relative;
    bool                                                    m_suspend_update;

    DrawSpace::Core::Task<DrawSpace::Core::Runner>*         m_task;

    DrawSpace::Core::Mediator*                              m_mediator;

    DrawSpace::Core::Mediator::Event*                       m_buildmeshe_event;

    DrawSpace::Utils::Mutex                                 m_meshe_ready_mutex;
    bool                                                    m_meshe_ready;

    DrawSpace::Core::Runner*                                m_runner;


    void on_planet_event( int p_currentface );

    void on_meshebuild_request( DrawSpace::Core::PropertyPool* p_args );

    void build_meshe( DrawSpace::Core::Meshe& p_patchmeshe, int p_patch_orientation, dsreal p_sidelength, dsreal p_xpos, dsreal p_ypos, DrawSpace::Core::Meshe& p_outmeshe );

public:

    MyPlanet( const dsstring& p_name, dsreal p_ray );
    ~MyPlanet( void );

    DrawSpace::Planet::Body* GetDrawable( void );
    DrawSpace::Dynamics::Orbiter*   GetOrbiter( void );
    DrawSpace::Dynamics::World*     GetWorld( void );

    bool GetCollisionState( void );

    dsreal GetAltitud( void );

    void AttachBody( DrawSpace::Dynamics::InertBody* p_body );
    void DetachBody( DrawSpace::Dynamics::InertBody* p_body );
    


    void ApplyGravity( void );

    void Update( DrawSpace::Dynamics::InertBody* p_player_body );

    bool IsPlayerRelative( void );

    void GetName( dsstring& p_name );

};


class dsAppClient : public DrawSpace::App
{
protected:

    static dsAppClient*                         m_instance;

    DrawSpace::Scenegraph                       m_scenegraph;


    DrawSpace::IntermediatePass*                m_texturepass;
    DrawSpace::FinalPass*                       m_finalpass;


    DrawSpace::Utils::TimeManager               m_timer;

    bool                                        m_mouselb;
    bool                                        m_mouserb;


    DrawSpace::Interface::FontImport*           m_font_import;
    DrawSpace::Core::Font*                      m_font;


    DrawSpace::Dynamics::CameraPoint*           m_camera;
    DrawSpace::Dynamics::CameraPoint*           m_camera2;

    DrawSpace::Dynamics::CameraPoint*           m_camera3;
    DrawSpace::Core::CircularMovement*          m_circular_mvt;

    DrawSpace::Dynamics::CameraPoint*           m_camera4;


    DrawSpace::Dynamics::CameraPoint*           m_curr_camera;

    DrawSpace::Core::FPSMovement                m_fpsmove;
    DrawSpace::Core::FreeMovement               m_freemove;
    
    DrawSpace::Interface::MesheImport*          m_meshe_import;

    
    DrawSpace::Spacebox*                        m_spacebox;
    

    dsreal                                      m_speed;
    dsreal                                      m_speed_speed;

    DrawSpace::Dynamics::World                  m_world;

    

    DrawSpace::Dynamics::Calendar*              m_calendar;


    MyPlanet*                                   m_planet;

    DrawSpace::Dynamics::Orbit*                 m_orbit;
    DrawSpace::Dynamics::Centroid*              m_centroid;


    MyPlanet*                                   m_moon;



    DrawSpace::Dynamics::Orbit*                 m_orbit2;
    DrawSpace::Dynamics::Centroid*              m_centroid2;


    DrawSpace::Dynamics::Rocket*                m_ship;
    

    DrawSpace::Chunk*                           m_ship_drawable;



    ///////////////////////////////////////////////////////////

    DrawSpace::Utils::Vector                    m_player_ship_gravity;

    DrawSpace::Utils::Matrix                    m_player_view_transform;

    DrawSpace::Utils::Vector                    m_player_view_pos;
    dsreal                                      m_player_view_linear_acc[3];
    dsreal                                      m_player_view_linear_acc_2[3];
    dsreal                                      m_player_view_linear_speed[3];

    dsreal                                      m_player_view_linear_speed_clamp_up[3];
    dsreal                                      m_player_view_linear_speed_clamp_down[3];


    dsreal                                      m_player_view_theta;
    dsreal                                      m_player_view_phi;
    dsreal                                      m_player_view_rho;

    dsreal                                      m_player_view_angular_acc[3];
    dsreal                                      m_player_view_angular_acc_2[3];

    dsreal                                      m_player_view_angular_speed_clamp_up[3];
    dsreal                                      m_player_view_angular_speed_clamp_down[3];

    dsreal                                      m_player_view_angular_speed[3];

    ////////////////////////////////////////////////////////////

    MyPlanet*                                   m_relative_planet;


    dsAppClient( void );

    void compute_player_view_transform( void );


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

    virtual DrawSpace::Dynamics::Rocket* GetPlayerShip( void );
    virtual void SetLastPlayerShipGravity( const DrawSpace::Utils::Vector& p_gravity );

    virtual void SetRelativePlanet( MyPlanet* p_planet );
};

#endif

