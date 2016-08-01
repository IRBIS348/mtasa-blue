/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/luadefs/CLuaCameraDefs.cpp
*  PURPOSE:     Lua camera definitions class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "StdInc.h"

void CLuaCameraDefs::LoadFunctions ( void )
{
    // Cam get funcs
    CLuaCFunctions::AddFunction ( "getCamera", GetCamera );
    CLuaCFunctions::AddFunction ( "getCameraViewMode", GetCameraViewMode );
    CLuaCFunctions::AddFunction ( "getCameraMatrix", GetCameraMatrix );
    CLuaCFunctions::AddFunction ( "getCameraTarget", GetCameraTarget );
    CLuaCFunctions::AddFunction ( "getCameraInterior", GetCameraInterior );
    CLuaCFunctions::AddFunction ( "getCameraGoggleEffect", GetCameraGoggleEffect );
    CLuaCFunctions::AddFunction ( "getCameraShakeLevel", GetCameraShakeLevel );
    CLuaCFunctions::AddFunction ( "getCameraFieldOfView", GetCameraFieldOfView );

    // Cam set funcs
    CLuaCFunctions::AddFunction ( "setCameraMatrix", SetCameraMatrix );
    CLuaCFunctions::AddFunction ( "setCameraFieldOfView", SetCameraFieldOfView );
    CLuaCFunctions::AddFunction ( "setCameraTarget", SetCameraTarget );
    CLuaCFunctions::AddFunction ( "setCameraInterior", SetCameraInterior );
    CLuaCFunctions::AddFunction ( "fadeCamera", FadeCamera );
    CLuaCFunctions::AddFunction ( "setCameraClip", SetCameraClip );
    CLuaCFunctions::AddFunction ( "getCameraClip", GetCameraClip );
    CLuaCFunctions::AddFunction ( "setCameraViewMode", SetCameraViewMode );
    CLuaCFunctions::AddFunction ( "setCameraGoggleEffect", SetCameraGoggleEffect );
    CLuaCFunctions::AddFunction ( "setCameraShakeLevel", SetCameraShakeLevel );
}

void CLuaCameraDefs::AddClass ( lua_State* luaVM )
{
    lua_newclass ( luaVM );

    lua_classfunction ( luaVM, "fade", "fadeCamera" );
    lua_classfunction ( luaVM, "resetFarClipDistance", "resetFarClipDistance" );
    lua_classfunction ( luaVM, "resetNearClipDistance", "resetNearClipDistance" );

    lua_classfunction ( luaVM, "getPosition", OOP_GetCameraPosition );
    lua_classfunction ( luaVM, "getRotation", OOP_GetCameraRotation );
    lua_classfunction ( luaVM, "getTarget", "getCameraTarget" );
    lua_classfunction ( luaVM, "getInterior", "getCameraInterior" );
    lua_classfunction ( luaVM, "getViewMode", "getCameraViewMode" );
    lua_classfunction ( luaVM, "getMatrix", OOP_GetCameraMatrix );
    lua_classfunction ( luaVM, "getFieldOfView", "getCameraFieldOfView" );
    lua_classfunction ( luaVM, "getGoggleEffect", "getCameraGoggleEffect" );
    lua_classfunction ( luaVM, "getClip", "getCameraClip" );
    lua_classfunction ( luaVM, "getFarClipDistance", "getFarClipDistance" );
    lua_classfunction ( luaVM, "getNearClipDistance", "getNearClipDistance" );

    lua_classfunction ( luaVM, "setPosition", OOP_SetCameraPosition );
    lua_classfunction ( luaVM, "setRotation", OOP_SetCameraRotation );
    lua_classfunction ( luaVM, "setMatrix", "setCameraMatrix" );
    lua_classfunction ( luaVM, "setFieldOfView", "setCameraFieldOfView" );
    lua_classfunction ( luaVM, "setInterior", "setCameraInterior" );
    lua_classfunction ( luaVM, "setTarget", "setCameraTarget" );
    lua_classfunction ( luaVM, "setViewMode", "setCameraViewMode" );
    lua_classfunction ( luaVM, "setGoggleEffect", "setCameraGoggleEffect" );
    lua_classfunction ( luaVM, "setClip", "setCameraClip" );
    lua_classfunction ( luaVM, "setFarClipDistance", "setFarClipDistance" );
    lua_classfunction ( luaVM, "setNearClipDistance", "setNearClipDistance" );

    lua_classvariable ( luaVM, "interior", "setCameraInterior", "getCameraInterior" );
    lua_classvariable ( luaVM, "target", "setCameraTarget", "getCameraTarget" );
    lua_classvariable ( luaVM, "viewMode", "setCameraViewMode", "getCameraViewMode" );
    lua_classvariable ( luaVM, "goggleEffect", "setCameraGoggleEffect", "getCameraGoggleEffect" );
    lua_classvariable ( luaVM, "farClipDistance", "setFarClipDistance", "getFarClipDistance" );
    lua_classvariable ( luaVM, "nearClipDistance", "setNearClipDistance", "getNearClipDistance" );

    lua_classvariable ( luaVM, "position", OOP_SetCameraPosition, OOP_GetCameraPosition );
    lua_classvariable ( luaVM, "rotation", OOP_SetCameraRotation, OOP_GetCameraRotation );
    lua_classvariable ( luaVM, "matrix", NULL, OOP_GetCameraMatrix );

    lua_registerstaticclass ( luaVM, "Camera" );
}


int CLuaCameraDefs::GetCamera ( lua_State* luaVM )
{
    CClientCamera* pCamera = g_pClientGame->GetManager ()->GetCamera ();
    if ( pCamera )
    {
        lua_pushelement ( luaVM, pCamera );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::GetCameraViewMode ( lua_State* luaVM )
{
    unsigned short ucMode;
    if ( CStaticFunctionDefinitions::GetCameraViewMode ( ucMode ) )
    {
        lua_pushnumber ( luaVM, ucMode );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaCameraDefs::GetCameraMatrix ( lua_State* luaVM )
{
    CVector vecPosition, vecLookAt;
    float fRoll, fFOV;
    if ( CStaticFunctionDefinitions::GetCameraMatrix ( vecPosition, vecLookAt, fRoll, fFOV ) )
    {
        lua_pushnumber ( luaVM, vecPosition.fX );
        lua_pushnumber ( luaVM, vecPosition.fY );
        lua_pushnumber ( luaVM, vecPosition.fZ );
        lua_pushnumber ( luaVM, vecLookAt.fX );
        lua_pushnumber ( luaVM, vecLookAt.fY );
        lua_pushnumber ( luaVM, vecLookAt.fZ );
        lua_pushnumber ( luaVM, fRoll );
        lua_pushnumber ( luaVM, fFOV );
        return 8;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::OOP_GetCameraMatrix ( lua_State* luaVM )
{
    CMatrix matrix;
    m_pManager->GetCamera ()->GetMatrix ( matrix );

    lua_pushmatrix ( luaVM, matrix );
    return 1;
}

int CLuaCameraDefs::GetCameraTarget ( lua_State* luaVM )
{
    CClientEntity* pTarget = CStaticFunctionDefinitions::GetCameraTarget ();
    if ( pTarget )
    {
        lua_pushelement ( luaVM, pTarget );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaCameraDefs::GetCameraInterior ( lua_State* luaVM )
{
    unsigned char ucInterior;
    if ( CStaticFunctionDefinitions::GetCameraInterior ( ucInterior ) )
    {
        lua_pushnumber ( luaVM, ucInterior );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::GetCameraGoggleEffect ( lua_State *luaVM )
{
    bool bNightVision = g_pMultiplayer->IsNightVisionEnabled ();
    bool bThermalVision = g_pMultiplayer->IsThermalVisionEnabled ();

    if ( bNightVision )
        lua_pushstring ( luaVM, "nightvision" );
    else if ( bThermalVision )
        lua_pushstring ( luaVM, "thermalvision" );
    else
        lua_pushstring ( luaVM, "normal" );

    return 1;
}

int CLuaCameraDefs::GetCameraShakeLevel ( lua_State* luaVM )
{
    //  int getCameraShakeLevel ()
    CPlayerInfo* pPlayerInfo = g_pGame->GetPlayerInfo ();
    if ( pPlayerInfo )
    {
        lua_pushnumber ( luaVM, pPlayerInfo->GetCamDrunkLevel () );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::SetCameraMatrix ( lua_State* luaVM )
{
    CVector vecPosition; CVector vecLookAt; float fRoll = 0.0f; float fFOV = 70.0f;
    CScriptArgReader argStream ( luaVM );

    if ( argStream.NextIsUserDataOfType <CLuaMatrix> () ) {
        CLuaMatrix* pMatrix;
        argStream.ReadUserData ( pMatrix );

        vecPosition = pMatrix->GetPosition ();
        vecLookAt = pMatrix->GetRotation ();
    }
    else
    {
        argStream.ReadVector3D ( vecPosition );
        argStream.ReadVector3D ( vecLookAt, CVector () );
    }

    argStream.ReadNumber ( fRoll, 0.0f );
    argStream.ReadNumber ( fFOV, 70.0f );
    if ( fFOV <= 0.0f || fFOV >= 180.0f )
        fFOV = 70.0f;

    if ( !argStream.HasErrors () )
    {
        if ( CStaticFunctionDefinitions::SetCameraMatrix ( vecPosition, &vecLookAt, fRoll, fFOV ) )
        {
            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}

// Only when onfoot/invehicle
int CLuaCameraDefs::SetCameraFieldOfView ( lua_State* luaVM )
{
    float fFOV; eFieldOfViewMode eMode;
    CScriptArgReader argStream ( luaVM );

    argStream.ReadEnumString ( eMode );
    argStream.ReadNumber ( fFOV );

    if ( !argStream.HasErrors () )
    {
        while ( true ) {
            if ( fFOV < 0 || fFOV > 179 ) {
                argStream.SetCustomError ( "Invalid FOV range (0-179)" );
                break;
            }

            if ( eMode == FOV_MODE_PLAYER )
                g_pGame->GetSettings ()->SetFieldOfViewPlayer ( fFOV );
            else if ( eMode == FOV_MODE_VEHICLE )
                g_pGame->GetSettings ()->SetFieldOfViewVehicle ( fFOV );
            else if ( eMode == FOV_MODE_VEHICLE_MAX )
                g_pGame->GetSettings ()->SetFieldOfViewVehicleMax ( fFOV );
            else {
                argStream.m_iIndex = 1;
                argStream.SetCustomError ( SString ( "Enum not yet implemented: " + EnumToString ( eMode ) ) );
                break;
            }

            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }

    m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );
    lua_pushboolean ( luaVM, false );
    return 1;
}

// Only when onfoot/invehicle
int CLuaCameraDefs::GetCameraFieldOfView ( lua_State* luaVM )
{
    eFieldOfViewMode eMode;
    CScriptArgReader argStream ( luaVM );

    argStream.ReadEnumString ( eMode );

    if ( !argStream.HasErrors () )
    {
        float fFOV;
        if ( eMode == FOV_MODE_PLAYER )
            fFOV = g_pGame->GetSettings ()->GetFieldOfViewPlayer ();
        else if ( eMode == FOV_MODE_VEHICLE )
            fFOV = g_pGame->GetSettings ()->GetFieldOfViewVehicle ();
        else if ( eMode == FOV_MODE_VEHICLE_MAX )
            fFOV = g_pGame->GetSettings ()->GetFieldOfViewVehicleMax ();
        else {
            argStream.m_iIndex = 1;
            m_pScriptDebugging->LogCustom ( luaVM, SString ( "Enum not yet implemented: " + EnumToString ( eMode ) ) );
            lua_pushboolean ( luaVM, false );
            return 1;
        }

        lua_pushnumber ( luaVM, fFOV );
        return 1;
    }

    m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );
    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::SetCameraTarget ( lua_State* luaVM )
{
    //  bool setCameraTarget ( element target = nil ) or setCameraTarget ( float x, float y, float z )

    CScriptArgReader argStream ( luaVM );
    if ( argStream.NextIsUserDataOfType<CClientEntity> () )
    {
        CClientEntity* pTarget;
        argStream.ReadUserData ( pTarget );

        if ( !argStream.HasErrors () )
        {
            if ( CStaticFunctionDefinitions::SetCameraTarget ( pTarget ) )
            {
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
    }
    else
    {
        CVector vecTarget;
        argStream.ReadVector3D ( vecTarget );

        if ( !argStream.HasErrors () )
        {
            if ( CStaticFunctionDefinitions::SetCameraTarget ( vecTarget ) )
            {
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
    }

    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaCameraDefs::SetCameraInterior ( lua_State* luaVM )
{
    unsigned char ucInterior = 0;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadNumber ( ucInterior );

    if ( !argStream.HasErrors () )
    {
        if ( CStaticFunctionDefinitions::SetCameraInterior ( ucInterior ) )
        {
            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaCameraDefs::FadeCamera ( lua_State* luaVM )
{
    bool bFadeIn = false;
    unsigned char ucRed = 0;
    unsigned char ucGreen = 0;
    unsigned char ucBlue = 0;
    float fFadeTime = 1.0f;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadBool ( bFadeIn );
    argStream.ReadNumber ( fFadeTime, 1.0f );
    argStream.ReadNumber ( ucRed, 0 );
    argStream.ReadNumber ( ucGreen, 0 );
    argStream.ReadNumber ( ucBlue, 0 );

    if ( !argStream.HasErrors () )
    {
        if ( CStaticFunctionDefinitions::FadeCamera ( bFadeIn, fFadeTime, ucRed, ucGreen, ucBlue ) )
        {
            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaCameraDefs::SetCameraClip ( lua_State* luaVM )
{
    bool bObjects = true;
    bool bVehicles = true;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadBool ( bObjects, true );
    argStream.ReadBool ( bVehicles, true );

    m_pManager->GetCamera ()->SetCameraClip ( bObjects, bVehicles );

    lua_pushboolean ( luaVM, true );
    return 1;
}

int CLuaCameraDefs::GetCameraClip ( lua_State* luaVM )
{
    bool bObjects, bVehicles;
    m_pManager->GetCamera ()->GetCameraClip ( bObjects, bVehicles );

    lua_pushboolean ( luaVM, bObjects );
    lua_pushboolean ( luaVM, bVehicles );
    return 2;
}

int CLuaCameraDefs::SetCameraViewMode ( lua_State* luaVM )
{
    unsigned short usViewMode = 0;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadNumber ( usViewMode );

    if ( !argStream.HasErrors () )
    {
        CStaticFunctionDefinitions::SetCameraViewMode ( usViewMode );

        lua_pushboolean ( luaVM, true );
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::SetCameraGoggleEffect ( lua_State *luaVM )
{
    SString strMode = "";
    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strMode );

    if ( !argStream.HasErrors () )
    {
        bool bSuccess = false;

        if ( strMode.compare ( "nightvision" ) == 0 )
        {
            g_pMultiplayer->SetNightVisionEnabled ( true );
            g_pMultiplayer->SetThermalVisionEnabled ( false );

            bSuccess = true;
        }
        else if ( strMode.compare ( "thermalvision" ) == 0 )
        {
            g_pMultiplayer->SetNightVisionEnabled ( false );
            g_pMultiplayer->SetThermalVisionEnabled ( true );

            bSuccess = true;
        }
        else if ( strMode.compare ( "normal" ) == 0 )
        {
            g_pMultiplayer->SetNightVisionEnabled ( false );
            g_pMultiplayer->SetThermalVisionEnabled ( false );

            bSuccess = true;
        }

        if ( bSuccess )
        {
            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::SetCameraShakeLevel ( lua_State* luaVM )
{
    //  bool setCameraShakeLevel ( int level )
    int drunkLevel;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadNumber ( drunkLevel );

    if ( !argStream.HasErrors () )
    {
        if ( drunkLevel >= 0 && drunkLevel <= 255 )
        {
            CPlayerInfo* pPlayerInfo = g_pGame->GetPlayerInfo ();
            if ( pPlayerInfo )
            {
                pPlayerInfo->SetCamDrunkLevel ( static_cast<byte> ( drunkLevel ) );
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
        else
            argStream.SetCustomError ( "Invalid range (0-255)" );
    }

    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::OOP_GetCameraPosition ( lua_State* luaVM )
{
    CVector vecPosition;
    m_pManager->GetCamera ()->GetPosition ( vecPosition );

    lua_pushvector ( luaVM, vecPosition );
    return 1;
}

int CLuaCameraDefs::OOP_SetCameraPosition ( lua_State* luaVM )
{
    CVector vecPosition;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadVector3D ( vecPosition );

    if ( !argStream.HasErrors () )
    {
        CClientCamera* pCamera = m_pManager->GetCamera ();
        if ( !pCamera->IsInFixedMode () )
        {
            pCamera->ToggleCameraFixedMode ( true );
        }

        pCamera->SetPosition ( vecPosition );

        lua_pushboolean ( luaVM, true );
        return 1;
    }
    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaCameraDefs::OOP_GetCameraRotation ( lua_State* luaVM )
{
    CVector vecPosition;
    m_pManager->GetCamera ()->GetRotationDegrees ( vecPosition );

    lua_pushvector ( luaVM, vecPosition );
    return 1;
}

int CLuaCameraDefs::OOP_SetCameraRotation ( lua_State* luaVM )
{
    CVector vecRotation;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadVector3D ( vecRotation );

    if ( !argStream.HasErrors () )
    {
        CClientCamera* pCamera = m_pManager->GetCamera ();
        if ( !pCamera->IsInFixedMode () )
        {
            pCamera->ToggleCameraFixedMode ( true );
        }

        pCamera->SetRotationDegrees ( vecRotation );

        lua_pushboolean ( luaVM, true );
        return 1;
    }
    lua_pushboolean ( luaVM, false );
    return 1;
}