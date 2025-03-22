#pragma once
#include <FutureState.h>

class FUserProfile;

class FSDesktop :
    public FutureState
{
public:


    void InitState() override;
    void UpdateState(float delta) override;
    void RenderState() override;
    void EndState() override;

    void SetUser(FUserProfile* profile)
    {
        m_Profile = profile;
    }

private:

    FUserProfile* m_Profile = nullptr;

};

