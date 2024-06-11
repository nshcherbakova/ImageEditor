
# ImageEditor
               
            
              
             
A Simple client/server(a server feature is under development) cross-platform image editor application for **Windows**, **Android OS**, **Mac**, and **iOS** with **OpenGL** filters.

The client app can edit images using self written and open source OpenGL filters. 

The client app can upload images to the server.

The server will keep collection of uploaded images and will show it in a web gallery.


- Used QT, OpenGL technologies and spdlog, gTest c++ libraries for the app
- Used Python and JavaScript for the server
- Used Jankins, Git hooks, Docker for infrastructure

![App main window](Images/Pixel1_1.jpg) *An effect of a window with drops.*



***


![Server](Images/server.jpg) *The web gallery with uploaded images.* 



***


![Uploading](Images/upload.jpg) *An image uploaded to the server.* 


***
                        
             
**ImageEditor** allows to apply some graphics filters to images.

![App main window](Images/Screenshot2.png)![App main window](Images/Screenshot1.png)![App main window](Images/Screen1_1.png).

*Emboss, sepia and a window with drops (a modified shader from BigWIngs https://www.shadertoy.com/) effects.*

***
           
           
## Goals

There are several goals of this project:

1. to make the project from an idea to a full value comfy GUI app through several steps: 
- making the UI concept 

![Main Sacreen](Images/ui_concep_Filters_screen.png) ![Dialog Sacreen](Images/ui_concept_Menu.png) ![Dialog Sacreen](Images/menu.png)

- making an app architecture
- choosing technologies and frameworks
- breaking to tasks and milestones
- writing a code
2. to train design skills: programming design patterns like Dependency Injection, Command
3. to make a **QT** based customized GUI app

![Kids](Images/screen_no_custom_450.png) -> ![Smooth](Images/flowers_aqua_sm_450.png)

4. to study how to build an Android app
5. to touch OpenGL ES shaders
6. to have a fun playing with bitmaps pixels while making simple filters from my university Machine Graphics classes
7. to play with Jankins
8. to explore testing and logging libraries
9. to make client / server app
10. to explore Docker container an compose
11. to explore git hooks
               
            
***

             
## Upcoming features:
1. translations
2. QML
3. UI animations
4. uploading images to the cloud
5. integration with social networks to uploading and downloading photos from/to there
6. add image editing tools and more complicated filters
               

***
              
             
**Dependences:**
- C++ 17 
- BOOST_DI_VERSION 1'2'0 (https://github.com/boost-ext/di)
- googletest-1.10.0 (https://github.com/google/googletest)
- spdlog (https://github.com/gabime/spdlog)
- Qt-6.4.2 (https://www.qt.io/download-qt-installer)
- uniassert (https://github.com/2gis/uniassert)

**Photo and pictures:**
- Natalya Shcherbakova 
- Anton Shcherbakov 
- Olga Demidova  
- Shutterstock

**Licenses:**
- LGPL
- used shader by Martijn Steinrucken License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
