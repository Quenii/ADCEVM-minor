#include "PcieDabEmulator.h"

using namespace gkhy::PcieDab2;

PcieDabEmulator::PcieDabEmulator(void)
: m_open(false)
{

}

PcieDabEmulator::~PcieDabEmulator(void)
{
	close();
}
