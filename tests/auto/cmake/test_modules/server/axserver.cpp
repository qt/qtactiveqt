
#include <QAxFactory>
#include <ActiveQt/QAxFactory>
#include <ActiveQt/ActiveQt>
#include <ActiveQt>

int main(int argc, char **argv)
{
    QAxFactory::isServer();
    return 0;
}
