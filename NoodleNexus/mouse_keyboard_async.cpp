// for non keyboard callback handling

#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>

#include "sharedThings.h"   // The camera, etc.
#include "sMesh.h"

#include "cLightManager.h"

//extern cLightManager* g_pLightManager;

// Defined in theMain.cpp
sMesh* pFindMeshByFriendlyName(std::string theNameToFind);

struct sMouseState
{
    glm::ivec2 currentPositionXY = glm::ivec2(0, 0);
    glm::ivec2 lastPositionXY = glm::ivec2(0, 0);
    bool bIsLeftMouseButtonDown = false;
};

sMouseState g_MouseState;

bool isShiftDown(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || 
        (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) )
    {
        return true;
    }
    return false;
}

bool isControlDown(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) ||
        (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
    {
        return true;
    }
    return false;
}

bool isAltDown(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) ||
        (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS))
    {
        return true;
    }
    return false;
}

bool areAllModifiersUp(GLFWwindow* window)
{
    if ( isShiftDown(window) ) 
    {
        return false;
    }

    if ( isControlDown(window) ) 
    {
        return false;
    }

    if ( isAltDown(window) ) 
    {
        return false;
    }

    // Nothing is down
    return true;
}

void handleMouseAsync(GLFWwindow* window)
{

//    if (glfwRawMouseMotionSupported())
//        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

//    std::cout << "Async mouse location (x,y): " << xpos << ", " << ypos << std::endl;

    return;
}

void handleKeyboardAsync(GLFWwindow* window)
{
    const float CAMERA_MOVE_SPEED = 1.0f;
    const float CAMERA_TURN_SPEED = 0.1f;

    if (isShiftDown(window))
    {
        // Keys move the selected target

        const float MESH_MOVE_SPEED = 0.05f;
        const float WIND_SPEED = 0.2f;

        cSoftBodyVerlet* pSB_Character = g_pPhysicEngine->pFindSoftBodyByFriendlyName("SoftBodyFlag");

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            pSB_Character->acceleration.x += WIND_SPEED;
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.z += MESH_MOVE_SPEED;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            pSB_Character->acceleration.x -= WIND_SPEED;
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.z -= MESH_MOVE_SPEED;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            pSB_Character->acceleration.z -= WIND_SPEED;
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.x -= MESH_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            pSB_Character->acceleration.z += WIND_SPEED;
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.x += MESH_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.y += MESH_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->positionXYZ.y -= MESH_MOVE_SPEED;
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->uniformScale *= 1.001;
            if (::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.z < 360)
            {
                ::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.z += 1;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            //::g_vecMeshesToDraw[g_selectedMeshIndex]->uniformScale *= 0.999;

            if (::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.z > 0)
            {
                ::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.z -= 1;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            if (::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.y < 360)
            {
                ::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.y += 1;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            if (::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.y > 0)
            {
                ::g_vecMeshesToDraw[g_selectedMeshIndex]->rotationEulerXYZ.y -= 1;
            }
        }
    }

    if (isControlDown(window))
    {
        // Keys move the selected light

        const float LIGHT_MOVE_SPEED = 0.02f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.z += LIGHT_MOVE_SPEED;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.z -= LIGHT_MOVE_SPEED;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.x -= LIGHT_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.x += LIGHT_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.y += LIGHT_MOVE_SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            ::g_pLightManager->theLights[g_selectedLightIndex].position.y -= LIGHT_MOVE_SPEED;
        }
        // Linear atten 1 & 2
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            // Increase linear (making it lighter)
            ::g_pLightManager->theLights[g_selectedLightIndex].atten.y *= 0.99f;     // Down 1%
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            // Increase linear (making it darker)
            ::g_pLightManager->theLights[g_selectedLightIndex].atten.y *= 1.01f;     // Up 1%
        }
        // Quadratic atten 3 & 4
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            // Quadratic linear (making it darker)
            // This is WAY more sensitive than the linear
            //  ...so you might want to change it by 0.1% (0.999)
            ::g_pLightManager->theLights[g_selectedLightIndex].atten.z *= 0.99f;    // Down 1%
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            // Quadratic linear (making it darker)
            ::g_pLightManager->theLights[g_selectedLightIndex].atten.z *= 1.01f;     // Up 1%
        }
        // HACK:Exit early
        return;
    }

    if (areAllModifiersUp(window))
    {
        
        // Move the camera 
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            // Go forward
            ::g_pFlyCamera->moveForward(CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.x += CHARACTER_MOVE_SPEED;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            // Go back
            ::g_pFlyCamera->moveForward(-CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.x -= CHARACTER_MOVE_SPEED;
        }
        else
        {
           // pSB_Character->acceleration.x = 0.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            // Go left
            ::g_pFlyCamera->moveLeftRight(CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.z -= CHARACTER_MOVE_SPEED;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            // Go right
            ::g_pFlyCamera->moveLeftRight(-CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.z += CHARACTER_MOVE_SPEED;
        }
        else
        {
            //pSB_Character->acceleration.z = 0.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            /*if (pSB_Character->acceleration.y < 2.0)
            {
                pSB_Character->acceleration.y += 1.0;
            }
            else
            {
                pSB_Character->acceleration.y = -3.0f;
            }*/
        }
        else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            // Go down
            ::g_pFlyCamera->moveUpDown(CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.y += CHARACTER_MOVE_SPEED;
        }
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            // Go up
            ::g_pFlyCamera->moveUpDown(-CAMERA_MOVE_SPEED);
            //pSB_Character->acceleration.y -= CHARACTER_MOVE_SPEED;
        }
        else
        {
            //pSB_Character->acceleration.y = -3.0f;
        }

        // Use the arrow keys to turn and pitch the camera

        // Left pitches negative (rotate around Y a negative value)
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            ::g_pFlyCamera->rotateLeftRight_Yaw(CAMERA_TURN_SPEED * 5.0);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            ::g_pFlyCamera->rotateLeftRight_Yaw(-CAMERA_TURN_SPEED * 5.0);
        }

        // Left pitches negative (rotate around Y a negative value)
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            ::g_pFlyCamera->pitchUpDown(-CAMERA_TURN_SPEED * 5.0);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            ::g_pFlyCamera->pitchUpDown(CAMERA_TURN_SPEED * 5.0);
        }

    }//if (areAllModifiersUp(window)

    return;
}
// *********************************************************
// Mouse callbacks:

// Set with glfwSetCursorPosCallback(window, cursor_position_callback);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
//    std::cout << "mouse x,y: " << xpos << ", " << ypos << std::endl;
    
    g_MouseState.currentPositionXY.x = (int)xpos;
    g_MouseState.currentPositionXY.y = (int)ypos;

    if ( g_MouseState.bIsLeftMouseButtonDown )
    {
        // If the Left mouse key is down, 
        //  figure out the differene between the current mouse postion and the last one

        glm::ivec2 deltaMousePosition = g_MouseState.lastPositionXY - g_MouseState.currentPositionXY;

        // Use those values to "turn" the camera
    
        // Move left or right? 
        if ( deltaMousePosition.x != 0 )
        {
            ::g_pFlyCamera->rotateLeftRight_Yaw( (float)deltaMousePosition.x );
        }
        // Mouse move Up or down? 
        if ( deltaMousePosition.y != 0 )
        {
            ::g_pFlyCamera->pitchUpDown((float)deltaMousePosition.y);
        }
    }//if ( g_MouseState.bIsLeftMouseButtonDown )


    // Update the last one
    g_MouseState.lastPositionXY = g_MouseState.currentPositionXY;

    //return;
}

// Set with glfwSetCursorEnterCallback(window, cursor_enter_callback);
void cursor_enter_callback(GLFWwindow* window, int entered)
{
    //if ( entered )
    //{
    //    std::cout << "Mouse is over the window" << std::endl;
    //}
    //else
    //{
    //    std::cout << "Mouse left the window" << std::endl;
    //}
    return;
}


// Set with glfwSetMouseButtonCallback(window, mouse_button_callback);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        switch (action)
        {
        case GLFW_PRESS:
//            std::cout << "GLFW_PRESS" << std::endl;
            g_MouseState.bIsLeftMouseButtonDown = true;
            break;
        case GLFW_RELEASE:
//            std::cout << "GLFW_RELEASE" << std::endl;
            g_MouseState.bIsLeftMouseButtonDown = false;
            break;
        default:
            std::cout << "Mouse button state unknown" << std::endl;
            break;
        }
    }

    return;
}

// Set with glfwSetScrollCallback(window, scroll_callback);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // For most mice, the value is the DIFFERENCE between the last time this was called!
    // (i.e. it's not an absolute value)
    // It also goes up and down along the Y axis and is an integer
//    std::cout << "xoffset, yoffset: " << xoffset << ", " << yoffset << std::endl;

    const float MOUSE_WHEEL_RATIO = 0.1f;

    ::g_pFlyCamera->adjustMovementSpeed( float(yoffset) * MOUSE_WHEEL_RATIO );

    return;
}



