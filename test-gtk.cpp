/*
 * Proof of concept to use GTK+ with with pure C++ 
 * (c) Régis FLORET 2011
 * 
 * This file is in the public domain
 */
 
 
#include <string>
#include <gtk/gtk.h>

/**
 * GTK namespace is in upper case to avoid conflict with Gtk:: en C
 */
namespace GTK {
    /**
     * The GTK base object 
     */
    class Object {
        public:
            /*
             * Default empty constructor to allow
             * <code>MyDerivatedObject obj</code>
             */
            Object() {} // ctor vide
            
            /**
             * Connect an object with a signal to a method
             
             * @param obj The object to connect
             * @param signal The signal to listen
             * @param callback The method or function to call
             * @param data Associated data
             */
            virtual void connect(GTK::Object * obj, gchar * signal, GCallback callback, gpointer data = NULL) {
                g_signal_connect(obj->object(), signal, callback, data);
            }
             
            /**
             * Must be implemented to return the real GTK Object
             
             * @return The GTK+ (GObject) object
             */
            virtual GObject * object() = 0; // Chaque objet renvoie ce qu'il gère
     };

    /**
     * Implement the GTKWindow in C++ (at least the minimal methods for this sample
     */
     class Window : public GTK::Object {
         public:
            /** 
             * Create the window. Default is normal window
             * @param type The GTK+ window type
             */
             Window(GtkWindowType type = GTK_WINDOW_TOPLEVEL) {
                 m_window = gtk_window_new(type);
             }
             
             /**
              * Set the window title
              * @param title The window title
              */
             inline void setTitle(const std::string title) {
                 gtk_window_set_title(GTK_WINDOW(m_window), title.c_str());
             }
             
             /**
              * Set the window title
              * @param title The window title
              */
             inline void setTitle(const gchar * title) {
                 gtk_window_set_title(GTK_WINDOW(m_window), title);
             }
             
            /**
             * Add a widget to the main container
             * @param toAdd The widget to add
             */
             inline void add(GtkWidget * toAdd) {
                 gtk_container_add(GTK_CONTAINER(m_window), toAdd);
             }
             
             /**
              * Display the window and all the contained widgets 
              */
             inline void show() {
                 gtk_widget_show_all(GTK_WIDGET(m_window));
             }
             
             /**
              * Implement the object() required method
              * @return The window as a GObject
              */
             inline GObject * object() {
                 return G_OBJECT(m_window);
             }
             
         protected:
             GtkWidget * m_window;
     };
 }

/**
 * Our derivated object
 */ 
class Window : public GTK::Window {
    public:
        Window() {
            connect(this, "destroy", G_CALLBACK(&Window::onCallback));
            setTitle("Hello world");
        }

        void onCallback() {
            gtk_main_quit();
        } 
};
 
/**
* Entry point
*/
int main(int argc, char ** argv)
{
    gtk_init(&argc , &argv);

    Window win;
    win.show();

    gtk_main();
    return 0;
}

