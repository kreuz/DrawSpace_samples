/*
*                                                                          
* DrawSpace Rendering engine                                               
* Emmanuel Chaumont Copyright (c) 2013-2016                              
*                                                                          
* This file is part of DrawSpace.                                          
*                                                                          
*    DrawSpace is free software: you can redistribute it and/or modify     
*    it under the terms of the GNU General Public License as published by  
*    the Free Software Foundation, either version 3 of the License, or     
*    (at your option) any later version.                                   
*                                                                          
*    DrawSpace is distributed in the hope that it will be useful,          
*    but WITHOUT ANY WARRANTY; without even the implied warranty of        
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
*    GNU General Public License for more details.                          
*                                                                          
*    You should have received a copy of the GNU General Public License     
*    along with DrawSpace.  If not, see <http://www.gnu.org/licenses/>.    
*
*/


#ifndef _DSAPPCLIENT_H_
#define _DSAPPCLIENT_H_

#include <dsapp.h>


class MultiFractalBinder : public DrawSpace::SphericalLOD::Binder
{
public:

    dsreal                                  m_plains_amplitude;
    dsreal                                  m_mountains_amplitude;
    dsreal                                  m_vertical_offset;
    dsreal                                  m_mountains_offset;

    dsreal                                  m_plains_seed1;
    dsreal                                  m_plains_seed2;
    dsreal                                  m_mix_seed1;
    dsreal                                  m_mix_seed2;

public:

    MultiFractalBinder( void );

    virtual void Bind( void );
    virtual void Unbind( void );
};

class PlanetClimateBinder : public MultiFractalBinder
{
protected:

public:

    PlanetClimateBinder( void );

    virtual void Bind( void );
    virtual void Unbind( void );
};

class PlanetLight
{
public:

    PlanetLight( void ) :
        m_enable( false )
    {
    };


    bool                                                    m_enable;
    DrawSpace::Utils::Vector                                m_color;
    DrawSpace::Utils::Vector                                m_dir;
    DrawSpace::Utils::Vector                                m_local_dir;

};

class PlanetDetailsBinder : public MultiFractalBinder
{
protected:

    dsreal                              m_innerRadius;
    dsreal                              m_outerRadius;
    DrawSpace::Utils::Vector            m_waveLength;
    dsreal                              m_kr;
    dsreal                              m_km;
    dsreal                              m_scaleDepth;

    dsreal                              m_skyfromspace_ESun;
    dsreal                              m_skyfromatmo_ESun;
    dsreal                              m_groundfromspace_ESun;
    dsreal                              m_groundfromatmo_ESun;

    DrawSpace::Utils::Vector            m_atmo_scattering_flags0;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags1;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags2;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags3;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags4;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags5;
    DrawSpace::Utils::Vector            m_atmo_scattering_flags6;


    DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>* m_planet_node;

    bool                                                    m_ambient;
    DrawSpace::Utils::Vector                                m_ambient_color;

    PlanetLight                                             m_lights[3];

    DrawSpace::Utils::Matrix                                m_planet_final_transform_rots;

    dsreal                                                  m_water_anim;


    DrawSpace::Core::Texture*                               m_clouds_texture;

    bool                                                    m_mirror_mode;

    dsreal                                                  m_ocean_details_alt;
    int                                                     m_water_bump_texture_resol;
    dsreal                                                  m_water_bump_factor;

    dsreal                                                  m_terrain_bump_factor;

public:

    PlanetDetailsBinder( dsreal p_planetRay, dsreal p_atmoThickness );

    virtual void Bind( void );
    virtual void Unbind( void );

    void SetPlanetNode( DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>* p_planet_node );
    void SetCloudsTexture( DrawSpace::Core::Texture* p_texture );

    void Update( void );

    void SetMirrorMode( bool p_state )
    {
        m_mirror_mode = p_state;
    }

    void SetWaterAnim( dsreal p_value )
    {
        m_water_anim = p_value;
    }

    dsreal GetOceansDetailsAlt( void ) { return m_ocean_details_alt; };

    PlanetLight GetLight( int p_index ) { return m_lights[p_index]; };
};

class CloudsResources
{
protected:

    
    DrawSpace::Procedural::RulesPackage*                            m_clouds_procedural_rules;
    DrawSpace::Procedural::RulesPackage*                            m_clouds_low_procedural_rules;

    DrawSpace::Clouds*                                              m_clouds;
    DrawSpace::Clouds*                                              m_clouds_low;
    

    DrawSpace::Core::SceneNode<DrawSpace::Clouds>*                  m_clouds_node;
    DrawSpace::Core::SceneNode<DrawSpace::Clouds>*                  m_clouds_low_node;

    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*    m_clouds_rot_node;
    DrawSpace::Core::Transformation*                                m_clouds_rot;
    

    DrawSpace::IntermediatePass*                                    m_pass;
    DrawSpace::IntermediatePass*                                    m_mirrorpass;
    DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>*      m_planet_node;
   
    //dsreal                                                          m_deg_rot;
    //dsreal                                                          m_deg_rot_speed;

    dsreal                                                          m_deg_long;
    dsreal                                                          m_deg_lat;

    dsreal                                                          m_deg_long_speed;
    dsreal                                                          m_deg_lat_speed;


    //DrawSpace::Utils::Vector                                        m_rot_axis;
    //DrawSpace::Utils::Vector                                        m_rot_axis_rot_axis;
    //dsreal                                                          m_deg_rot_axis;



    void compute_clouds_vector_global( DrawSpace::Utils::Vector& p_out ); //calcul vector position champ nuage par rapport au centre planete exprim� dans le repere global

public:

    CloudsResources( DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>* p_planet_node, DrawSpace::IntermediatePass* p_pass, DrawSpace::IntermediatePass* p_mirrorpass );
    ~CloudsResources( void );

    //void Init( const dsstring& p_id, DrawSpace::Core::SceneNodeGraph& p_scenegraph, int p_seed, const DrawSpace::Utils::Vector& p_deg_rots, const DrawSpace::Utils::Vector& p_deg_rots_speeds );

    void Init( const dsstring& p_id, DrawSpace::Core::SceneNodeGraph& p_scenegraph, int p_seed, 
                    dsreal p_deg_init_lat, dsreal p_deg_init_long, dsreal p_deg_lat_speed, dsreal p_deg_long_speed );

    void ComputeLight( DrawSpace::Utils::Vector& p_ldir, DrawSpace::Utils::Vector& p_lcolor );
    void ComputeAlt( dsreal p_alt );
    void UpdateMirror( const DrawSpace::Utils::Vector& p_viewpos, const DrawSpace::Utils::Vector& p_planetpos );

    void SetCurrentCamera( DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>* p_cam );

    void Evolve( DrawSpace::Dynamics::Calendar& p_cald );

    void UpdateLongLatPos( dsreal p_long, dsreal p_lat );

    void CloudsUpdateRequest( void );

    friend class CloudsStateMachine;
};

class CloudsStateMachine
{
protected:

    std::vector<CloudsResources*>   m_volumetrics_clouds;

public:
    CloudsStateMachine( int p_nbCloudsField, DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>* p_planet_node, 
                        DrawSpace::IntermediatePass* p_pass, DrawSpace::IntermediatePass* p_mirrorpass, 
                        DrawSpace::Core::SceneNodeGraph& p_scenegraph );

    ~CloudsStateMachine( void );

    void ComputeLight( DrawSpace::Utils::Vector& p_ldir, DrawSpace::Utils::Vector& p_lcolor );
    void ComputeAlt( dsreal p_alt );
    void UpdateMirror( const DrawSpace::Utils::Vector& p_viewpos, const DrawSpace::Utils::Vector& p_planetpos );

    void SetCurrentCamera( DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>* p_cam );

    void Evolve( DrawSpace::Dynamics::Calendar& p_cald );

    void UpdateLongLatPos( dsreal p_long, dsreal p_lat );

    void CloudsUpdateRequest( void );
};


class dsAppClient : public DrawSpace::App
{
protected:

    typedef DrawSpace::Core::CallBack<dsAppClient, void, DrawSpace::Gui::Widget*>   WidgetEventHandler;

    typedef DrawSpace::Core::CallBack<dsAppClient, void, DrawSpace::Utils::Timer*> TimerCb;


    static dsAppClient*                         m_instance;

    DrawSpace::Interface::Renderer::DeviceDescr m_deviceDescr;

    DrawSpace::Core::SceneNodeGraph             m_scenenodegraph;

    bool                                        m_showinfos;


    TimerCb*                                    m_timer_cb;

    DrawSpace::Utils::Timer*                    m_period_timer;


    DrawSpace::IntermediatePass*                m_texturepass;    
    DrawSpace::IntermediatePass*                m_texturemirrorpass;
    DrawSpace::IntermediatePass*                m_wavespass;
    DrawSpace::IntermediatePass*                m_waterbumppass;

    DrawSpace::IntermediatePass*                m_occlusionpass;
    DrawSpace::IntermediatePass*                m_zoompass;

    void*                                       m_zoom_texture_content;

    DrawSpace::FinalPass*                       m_finalpass;
    DrawSpace::FinalPass*                       m_finalpass2;


    DrawSpace::Utils::TimeManager               m_timer;


    std::default_random_engine                  m_cloudspos_generator;
    

    bool                                        m_mouselb;
    bool                                        m_mouserb;


    DrawSpace::Interface::FontImport*           m_font_import;
    DrawSpace::Core::Font*                      m_font;


    DrawSpace::Spacebox*                        m_spacebox;
    DrawSpace::Core::SceneNode<DrawSpace::Spacebox>*                    m_spacebox_node;


    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*        m_spacebox_transfo_node;


    DrawSpace::Dynamics::CameraPoint*           m_camera3;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>*       m_camera3_node;

    

    DrawSpace::Dynamics::CameraPoint*           m_camera5;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>*       m_camera5_node;
    DrawSpace::Core::LongLatMovement*           m_longlat_mvt;
    DrawSpace::Core::SceneNode<DrawSpace::Core::LongLatMovement>*          m_longlatmvt_node;
    DrawSpace::Core::FPSMovement*              m_fps_mvt;
    DrawSpace::Core::SceneNode<DrawSpace::Core::FPSMovement>*          m_fpsmvt_node;


    DrawSpace::Core::CircularMovement*          m_circular_mvt;
    DrawSpace::Core::SceneNode<DrawSpace::Core::CircularMovement>*          m_circmvt_node;

    DrawSpace::Core::SceneNode<DrawSpace::Core::Transformation>*        m_camera_transfo_node;
    


    DrawSpace::Core::LongLatMovement*           m_longlat_mvt3;
    DrawSpace::Core::SceneNode<DrawSpace::Core::LongLatMovement>*          m_longlatmvt3_node;


    DrawSpace::Core::LongLatMovement*           m_longlat_mvt4;
    DrawSpace::Core::SceneNode<DrawSpace::Core::LongLatMovement>*          m_longlatmvt4_node;


    DrawSpace::Dynamics::CameraPoint*           m_curr_camera;
    dsstring                                    m_curr_camera_name;


    DrawSpace::Dynamics::CameraPoint*                                       m_camera_occ;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::CameraPoint>*           m_camera_occ_node;


    
    DrawSpace::Interface::MesheImport*          m_meshe_import;

    
    

    dsreal                                      m_speed;
    dsreal                                      m_speed_speed;

    DrawSpace::Dynamics::World                  m_world;

    

    DrawSpace::Dynamics::Calendar*              m_calendar;


    DrawSpace::Core::Fx*                                   m_details_fx;
    DrawSpace::Core::Fx*                                   m_clouds_fx;
    DrawSpace::Core::Fx*                                   m_clouds_mirror_fx;


    DrawSpace::Dynamics::Orbit*                                         m_planet_orbit;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::Orbit>*             m_planet_orbit_node;
    
    DrawSpace::SphericalLOD::Root*                                      m_planet;
    DrawSpace::Core::SceneNode<DrawSpace::SphericalLOD::Root>*          m_planet_node;

    

    MultiFractalBinder*                                                 m_planet_collisions_binder[6];

    PlanetClimateBinder*                                                m_planet_climate_binder[6];

    PlanetDetailsBinder*                                                m_planet_detail_binder[6];


    PlanetDetailsBinder*                                                m_planet_atmosphere_binder[6];
    PlanetDetailsBinder*                                                m_planet_atmosphere_binder_mirror[6];

    PlanetDetailsBinder*                                                m_planet_clouds_binder[6];
    PlanetDetailsBinder*                                                m_planet_cloudslow_binder[6];
    PlanetDetailsBinder*                                                m_planet_clouds_binder_mirror[6];

    DrawSpace::SphericalLOD::Binder*                                    m_planet_waterbump_binder[6];

    DrawSpace::SphericalLOD::Binder*                                    m_planet_occlusion_binder[6];

    DrawSpace::Chunk*                                                   m_star_impostor;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                       m_star_impostor_node;

    DrawSpace::Chunk*                                                   m_starhalo_impostor;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                       m_starhalo_impostor_node;


    DrawSpace::Dynamics::Rocket*                m_ship;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::Rocket>*                    m_ship_node;
    

    DrawSpace::Chunk*                           m_ship_drawable;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                    m_ship_drawable_node;



    DrawSpace::Chunk*                           m_building;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                    m_building_node;
    
    DrawSpace::Dynamics::Collider*              m_building_collider;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::Collider>*                    m_building_collider_node;

    DrawSpace::Chunk*                           m_socle;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                    m_socle_node;
    DrawSpace::Dynamics::Collider*              m_socle_collider;
    DrawSpace::Core::SceneNode<DrawSpace::Dynamics::Collider>*                    m_socle_collider_node;

    dsstring                                    m_timefactor;

    DrawSpace::Core::RenderingNode*             m_flatcloudshigh_rnode[6];
    DrawSpace::Core::RenderingNode*             m_flatcloudslow_rnode[6];

    CloudsStateMachine*                         m_clouds_state_machine;

    ///////////////////////////////////////////////////////////


    DrawSpace::Gui::ReticleWidget*              m_reticle_widget;
    DrawSpace::Gui::TextWidget*                 m_text_widget;
    DrawSpace::Gui::TextWidget*                 m_text_widget_2;


    bool                                        m_final_pass_2;


    DrawSpace::SystemMouseInputProvider         m_mouse_input;

    WidgetEventHandler*                         m_mouseleftbuttondown_eventhandler;

    bool                                        m_ready;

    int                                         m_init_count;

    dsreal                                      m_water_anim;
    bool                                        m_water_anim_inc;


    bool                                        m_walking;
    dsreal                                      m_walking_long;
    dsreal                                      m_walking_lat;
    dsreal                                      m_walking_speed;

    bool                                        m_haslanded;

    DrawSpace::Utils::Vector                    m_playerpos_longlatalt;

    DrawSpace::Utils::Vector                    m_shippos_longlatalt;
    
    dsreal                                      m_ship_walker_distance;

    bool                                        m_can_leave;
    bool                                        m_can_join;
   
    void init_planet_meshes( void );
    void init_assets_loaders( void );
    void init_passes( void );
    void init_world_physics( void );
    void init_spacebox( void );
    void init_buildings( void );
    void init_planet( void );
    void init_ship( void );
    void init_star_impostor( void );
    void init_cameras( void );
    void init_reticle( void );
    void init_text_assets( void );
    void init_rendering_queues( void );
    void init_calendar( void );
    void init_planet_noise( void );

    void render_universe( void );

    void print_init_trace( const dsstring& p_string );

    void on_mouseleftbuttondown( DrawSpace::Gui::Widget* p_widget );

    void on_timer( DrawSpace::Utils::Timer* p_timer );


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

