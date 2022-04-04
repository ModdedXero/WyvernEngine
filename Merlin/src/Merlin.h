#pragma once

// For use by Thorn Applications
#include <stdio.h>

#include <Merlin/Core/Application.h>
#include <Merlin/Core/Layer.h>
#include <Merlin/Core/Timestep.h>

#include <Merlin/Core/Scene/Scene.h>
#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Core/Scene/Wizard.h>
#include <Merlin/Core/Scene/EntityList.h>

// Components
#include <Merlin/Core/Scene/Component.h>
#include <Merlin/Core/Scene/Transform.h>
#include <Merlin/Renderer/Material2D.h>
#include <Merlin/Core/Physics/Collider2D.h>
#include <Merlin/Core/Physics/RigidBody2D.h>
#include <Merlin/UI/Button.h>

#include <Merlin/Core/Math/Math.h>

#include <Merlin/Renderer/ResourceManager.h>
#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Renderer/Camera.h>

#include <Merlin/Core/Input.h>

#include <Merlin/Events/Event.h>
#include <Merlin/Events/KeyEvent.h>
#include <Merlin/Events/WindowEvent.h>

#include <Merlin/Core/Debug.h>