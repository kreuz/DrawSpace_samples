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


class dsAppClient : public DrawSpace::App
{
protected:

    typedef DrawSpace::Core::CallBack<dsAppClient, void, DrawSpace::Gui::Widget*>   WidgetEventHandler;

    static dsAppClient*                                                             m_instance;

    DrawSpace::FinalPass*                                                           m_finalpass;
    DrawSpace::IntermediatePass*                                                    m_texturepass;
    
    DrawSpace::Core::SceneNodeGraph                                                 m_scenenodegraph;

    DrawSpace::Interface::FontImport*                                               m_font_import;
    DrawSpace::Core::Font*                                                          m_font;

    dsreal                                                                          m_yangle;
    dsreal                                                                          m_xangle;
    dsreal                                                                          m_zangle;
    DrawSpace::Utils::TimeManager                                                   m_timer;

    bool                                                                            m_mouselb;

    DrawSpace::Image*                                                               m_image1;

    long                                                                            m_xmouse;
    long                                                                            m_ymouse;

    DrawSpace::Gui::TextWidget*                                                     m_text_widget;

    DrawSpace::Gui::TextWidget*                                                     m_fpstext_widget;

    DrawSpace::Gui::TextWidget*                                                     m_text_widget_2;

    DrawSpace::Gui::TextWidget*                                                     m_text_widget_3;

    //DrawSpace::SystemMouseInputProvider                                             m_mouse_input;
    DrawSpace::ImageMouseInputProvider                                              m_mouse_input;

    DrawSpace::Interface::MesheImport*                                              m_meshe_import;
    DrawSpace::Chunk*                                                               m_chunk;
    DrawSpace::Core::SceneNode<DrawSpace::Chunk>*                                   m_chunk_node;


    WidgetEventHandler*                                                             m_mousein_eventhandler;
    WidgetEventHandler*                                                             m_mouseout_eventhandler;
    WidgetEventHandler*                                                             m_mouseleftbuttondown_eventhandler;
    WidgetEventHandler*                                                             m_mouseleftbuttonup_eventhandler;
    WidgetEventHandler*                                                             m_mouserightbuttondown_eventhandler;
    WidgetEventHandler*                                                             m_mouserightbuttonup_eventhandler;


    dsreal                                                                          m_widget_rot;


    dsAppClient( void );

    void on_mousein( DrawSpace::Gui::Widget* p_widget );
    void on_mouseout( DrawSpace::Gui::Widget* p_widget );
    void on_mouseleftbuttondown( DrawSpace::Gui::Widget* p_widget );
    void on_mouseleftbuttonup( DrawSpace::Gui::Widget* p_widget );
    void on_mouserightbuttondown( DrawSpace::Gui::Widget* p_widget );
    void on_mouserightbuttonup( DrawSpace::Gui::Widget* p_widget );

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

