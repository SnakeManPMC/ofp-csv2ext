#include <QtCore/QCoreApplication>
#include "csv2ext.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    csv2Ext(argc, argv);

	return 0;
}
