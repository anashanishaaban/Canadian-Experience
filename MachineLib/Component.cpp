/**
 * @file Component.cpp
 * @author Anas Shaaban
 */

#include "pch.h"
#include "Component.h"

/**
 * Constructor
 */
void Component::SetPosition(wxPoint position)
{
    mPosition = position;
}

/**
 * Get the position of the component
 * @return The position of the component
 */
wxPoint Component::GetPosition() const
{
    return mPosition;
}

/**
 * Set the image directory for loading assets
 * @param directory The directory to load images from
 */
void Component::SetImageDirectory(const std::wstring& directory)
{
    mImageDirectory = directory;
}

/**
 * Get the image directory
 * @return The image directory
 */
std::wstring Component::GetImageDirectory() const
{
    return mImageDirectory;
}

/**
 * Reset the component
 */
void Component::Reset()
{
    mTime = 0.0;
}

/**
 * Update the component
 * @param elapsedTime The time elapsed since the last update
 */
void Component::Update(double elapsedTime)
{
    mTime += elapsedTime;
}