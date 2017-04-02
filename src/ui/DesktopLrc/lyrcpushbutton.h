#ifndef LYRCPUSHBUTTON_H
#define LYRCPUSHBUTTON_H
#include <QPushButton>

class LyrcPushButton : public QPushButton
{
public:
    explicit LyrcPushButton(QWidget *parent = 0);
    ~LyrcPushButton();

private:
    void initForm();
};

#endif // LYRCPUSHBUTTON_H
