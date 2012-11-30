
#include <QAxFactory>
#include <ActiveQt/QAxFactory>
#include <ActiveQt/ActiveQt>
#include <ActiveQt>


QT_BEGIN_NAMESPACE
QAxFactory *qax_instantiate()
{
    return 0;
}
QT_END_NAMESPACE

int main(int argc, char **argv)
{
    QAxFactory::isServer();
    return 0;
}
