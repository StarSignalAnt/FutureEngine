#pragma once
#include <FPApp.h>

class ITextEdit;
class ITextArea;

class FutureTalk :
    public FPApp
{
public:

    FutureTalk();

    void InitApp() override;

private:
    ITextEdit* m_Question;
    ITextArea* m_Answer;
};

