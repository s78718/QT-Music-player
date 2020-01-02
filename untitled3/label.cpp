#include "label.h"

label::label()
{

}

void label::mousePressEvent()
{
    emit Mouse_Pressed();
}
