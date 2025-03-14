#pragma once
#include "IControl.h"
#include "UIHelp.h"
#include "GameInput.h"
class IVerticalScroller : public IControl
{
public:
    IVerticalScroller() : IControl(), m_ContentHeight(0), m_ScrollPosition(0), m_ScrollButtonSize(0),
        m_IsScrolling(false), m_ScrollTrackColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
        m_ScrollButtonColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f)), m_ScrollButtonWidth(15.0f) {
    }

    IVerticalScroller(glm::vec2 position, glm::vec2 size)
        : IControl(position, size), m_ContentHeight(0), m_ScrollPosition(0), m_ScrollButtonSize(0),
        m_IsScrolling(false), m_ScrollTrackColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
        m_ScrollButtonColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f)), m_ScrollButtonWidth(15.0f) {
    }

    // Set the total content height that needs to be scrolled
    void SetContentHeight(float height)
    {
        m_ContentHeight = height;
        UpdateScrollButtonSize();
    }

    // Get the current scroll position (0.0 to 1.0)
    float GetScrollPosition() const { return m_ScrollPosition; }

    // Set scroll position manually (0.0 to 1.0)
    void SetScrollPosition(float position)
    {
        m_ScrollPosition = glm::clamp(position, 0.0f, 1.0f);
        Scrolled();
    }

    // Set colors for the scrollbar
    void SetScrollTrackColor(const glm::vec4& color) { m_ScrollTrackColor = color; }
    void SetScrollButtonColor(const glm::vec4& color) { m_ScrollButtonColor = color; }

    // Set the width of the scroll button
    void SetScrollButtonWidth(float width) { m_ScrollButtonWidth = width; }

    // Calculate the visible ratio and update the scroll button size
    void UpdateScrollButtonSize()
    {
        if (m_ContentHeight <= m_Size.y)
        {
            // Content fits within the visible area
            m_ScrollButtonSize = m_Size.y;
        }
        else
        {
            // Calculate the ratio of visible content to total content
            float visibleRatio = m_Size.y / m_ContentHeight;
            m_ScrollButtonSize = glm::max(m_Size.y * visibleRatio, 20.0f); // Minimum size of 20 pixels
        }
    }

    // Get the current content offset (how many pixels to offset the content)
    float GetContentOffset() const
    {
        if (m_ContentHeight <= m_Size.y)
            return 0.0f;

        return m_ScrollPosition * (m_ContentHeight - m_Size.y);
    }

    // Override the Update method from IControl
    void Update(float delta) override
    {
        UpdateScrollButtonSize();
    }

    // Override the Render method from IControl
    void Render() override
    {
        // Rendering logic for the scrollbar would go here
        // This would typically involve drawing:
        // 1. The scroll track (background)
        // 2. The scroll button (thumb)
        glm::vec2 renderPos = GetRenderPosition();

        // Draw the scroll track (background)
        UIHelp::DrawRect(renderPos, glm::vec2(m_ScrollButtonWidth, m_Size.y), m_ScrollTrackColor);

        // Only draw the scroll button if content requires scrolling
        if (m_ContentHeight > m_Size.y)
        {
            // Calculate the position of the scroll button
            float buttonTop = renderPos.y + m_ScrollPosition * (m_Size.y - m_ScrollButtonSize);
            glm::vec2 buttonPos = glm::vec2(renderPos.x, buttonTop);

            // Draw the scroll button (thumb)
            UIHelp::DrawRect(buttonPos, glm::vec2(m_ScrollButtonWidth, m_ScrollButtonSize), m_ScrollButtonColor);
        }

        // Render children controls (if any)
        RenderChildren();

        // Note: The actual rendering would depend on your rendering system
        // This is a placeholder for the rendering logic
    }

    // Override mouse handling for scroll interaction
    void OnMouseDown(int button) override
    {
        if (button == 0) // Left mouse button
        {
            glm::vec2 mousePos = GameInput::MousePosition; /* Get mouse position from your input system */;
            glm::vec2 renderPos = GetRenderPosition();

            // Check if the click is on the scroll button
            if (IsPointOnScrollButton(mousePos))
            {
                m_IsScrolling = true;
                m_LastMouseY = mousePos.y;
            }
            else if (mousePos.x >= renderPos.x && mousePos.x <= renderPos.x + m_Size.x)
            {
                // Click on the track - jump to that position
                float relativeY = mousePos.y - renderPos.y;
                float newPos = relativeY / m_Size.y;
                SetScrollPosition(newPos);
            }
        }
    }

    void OnMouseUp(int button) override
    {
        if (button == 0) // Left mouse button
        {
            m_IsScrolling = false;
        }
    }

    void OnMouseMove(glm::vec2 position, glm::vec2 delta) override
    {
        if (m_IsScrolling)
        {
            // Calculate the scroll movement
            float deltaY = position.y - m_LastMouseY;
            float scrollDelta = deltaY / (m_Size.y - m_ScrollButtonSize);

            // Update the scroll position
            SetScrollPosition(m_ScrollPosition + scrollDelta);

            m_LastMouseY = position.y;
        }
    }

    void OnMouseWheel(float delta) override
    {
        // Scroll up or down based on the wheel delta
        // Typical scroll amount is 0.1 (10% of the visible area)
        float scrollAmount = 0.1f;
        SetScrollPosition(m_ScrollPosition - delta * scrollAmount);
    }
    void SetOnScrolled(std::function<void(float)> callback) {
        OnScrolled = callback;
    }
    void Scrolled() {

        if (OnScrolled) {
            OnScrolled(GetContentOffset());
        }

    }
    void Fix() {

        if (GetContentOffset() > m_ContentHeight)
        {
            auto v = m_ScrollPosition * m_ContentHeight;
            v = v - 0.1;
            if (m_ScrollPosition > v) {
                m_ScrollPosition = v;
                Scrolled();
            }

           // m_ScrollPosition = 

        }

    }
private:
    float m_ContentHeight;        // Total height of content to scroll
    float m_ScrollPosition;       // Current scroll position (0.0 to 1.0)
    float m_ScrollButtonSize;     // Height of the scroll button/thumb
    bool m_IsScrolling;           // Is the user currently dragging the scroll button?
    float m_LastMouseY;           // Last mouse Y position when scrolling
    glm::vec4 m_ScrollTrackColor; // Color of the scroll track
    glm::vec4 m_ScrollButtonColor; // Color of the scroll button
    float m_ScrollButtonWidth;    // Width of the scroll button

    // Helper method to check if a point is on the scroll button
    bool IsPointOnScrollButton(const glm::vec2& point)
    {
        glm::vec2 renderPos = GetRenderPosition();
        float buttonTop = renderPos.y + m_ScrollPosition * (m_Size.y - m_ScrollButtonSize);
        float buttonBottom = buttonTop + m_ScrollButtonSize;

        return (point.x >= renderPos.x &&
            point.x <= renderPos.x + m_ScrollButtonWidth &&
            point.y >= buttonTop &&
            point.y <= buttonBottom);
    }

    std::function<void(float)> OnScrolled = nullptr;
   
};