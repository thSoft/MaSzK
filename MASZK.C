/*               MaSzK               */
/* Magyar Sz”veges Kalandj t‚k-motor */

/* F‹program */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "alap.h"
#include "vilag.h"
#include "kezelok.h"
#include "fajl.h"
#include "jatek.h"

int main(int argc, char *argv[])
{
	ujvilag();
	betoltb();
	if ((argc == 1) && (!(*jatekfn)))
	{
		puts(U_PS);
		vilagvege();
		return -1;
	}
	switch (betoltfk(argc>1?argv[1]:jatekfn))
	{
		case -1: hiba(U_FAJL); break;
		case -2: vilagvege(); return -1;
		case -3: hiba(U_FK);
	}
	vanbev = (argc > 1);
	if ((*mentesfn) && (argc == 1))
	{
		switch (betoltm(mentesfn))
		{
			case -2: writeln(U_ROSSZM);
			case -1: case -3: *mentesfn = 0;
		}
	}
	fociklus();
	elmentb();
	vilagvege();
	return 0;
}
