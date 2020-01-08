/* MaSzK */
/* A kalandj t‚k vil g nak adatszerkezetei */

/* T¡pusok */

typedef struct
{
	byte tipus;
	word sorszam;
	byte allapot;
} Allapot;

typedef struct
{
	word parameter, uzenet;
	byte szallapot;
	Allapot *allapot;
} EsemenyP;

typedef struct
{
	word uzenet;
	byte szallapot;
	Allapot *allapot;
} Esemeny;

typedef struct
{
	byte allapot, idozito, szallapot, ido;
	word nev, leiras;
	byte kijaratok[12];
	byte sotet;
	Esemeny belep, kimegy;
	EsemenyP lejar;
} Helyiseg0;

typedef struct
{
	byte idozito;
	word leiras;
	byte sotet;
	Esemeny belep, kimegy;
	EsemenyP lejar;
} Helyiseg;

typedef struct
{
	byte allapot, idozito, szallapot, ido;
	word elotag, nev, leiras;
	byte helyiseg, hely;
	byte szereplonel, szer, rogzitett, nevelo;
	Esemeny vizsgal, felvesz, letesz;
	EsemenyP lejar;
	byte szakcio, szeszkoz;
	Lista *akcio, *eszkoz;
} Targy0;

typedef struct
{
	byte idozito;
	word leiras;
	byte helyiseg;
	byte szereplonel;
	Esemeny vizsgal, felvesz, letesz;
	EsemenyP lejar;
	byte szakcio, szeszkoz;
	Lista *akcio, *eszkoz;
} Targy;

typedef struct
{
	byte allapot, idozito, szallapot, ido;
	word nev, leiras;
	byte egyik, masik;
	byte jarhato;
	Esemeny vizsgal;
	EsemenyP lejar;
	byte szakcio, szeszkoz;
	Lista *akcio, *eszkoz;
} Akadaly0;

typedef struct
{
	byte idozito;
	word leiras;
	byte jarhato;
	Esemeny vizsgal;
	EsemenyP lejar;
	byte szakcio, szeszkoz;
	Lista *akcio, *eszkoz;
} Akadaly;

typedef struct
{
	byte allapot, idozito, szallapot, ido;
	word nev, koznev, leiras;
	byte helyiseg, hely, irany;
	byte iranyithato, egyedi;
	Esemeny vizsgal, iranyit;
	EsemenyP lejar, lep;
	byte szbeszel, szad, szmutat, szakcio, szeszkoz, szmeglat;
	Lista *beszel, *ad, *mutat, *akcio, *eszkoz, *meglat;
} Szereplo0;

typedef struct
{
	byte idozito;
	word leiras;
	byte helyiseg, irany;
	Esemeny vizsgal, iranyit;
	EsemenyP lejar, lep;
	byte szbeszel, szad, szmutat, szakcio, szeszkoz, szmeglat;
	Lista *beszel, *ad, *mutat, *akcio, *eszkoz, *meglat;
} Szereplo;

/* Makr¢k */

#define e_helyiseg0 ((Helyiseg0 *)(p0->info))
#define e_helyiseg ((Lista *)(p->info))
#define e_helyisega ((Helyiseg *)(pa->info))
#define e_targy0 ((Targy0 *)(p0->info))
#define e_targy ((Lista *)(p->info))
#define e_targya ((Targy *)(pa->info))
#define e_akadaly0 ((Akadaly0 *)(p0->info))
#define e_akadaly ((Lista *)(p->info))
#define e_akadalya ((Akadaly *)(pa->info))
#define e_szereplo0 ((Szereplo0 *)(p0->info))
#define e_szereplo ((Lista *)(p->info))
#define e_szereploa ((Szereplo *)(pa->info))
#define e_esemenyp1	((EsemenyP *)(pe1->info))
#define e_esemenyp2 ((EsemenyP *)(pe2->info))
#define e_esemenyp3 ((EsemenyP *)(pe3->info))
#define e_esemenyp4 ((EsemenyP *)(pe4->info))
#define e_esemenyp5 ((EsemenyP *)(pe5->info))
#define e_esemenyp6 ((EsemenyP *)(pe6->info))
#define aszoveg(x) ((char *)(elem(szoveg, x)->info))
#define ahelyiseg(x, a) ((Helyiseg *)(elem(((Lista *)(elem(helyiseg, x-1)->info)), a-1)->info))
#define ahelyiseg0(x) ((Helyiseg0 *)(elem(helyiseg0, x-1)->info))
#define atargy(x, a) ((Targy *)(elem(((Lista *)(elem(targy, x-1)->info)), a-1)->info))
#define atargy0(x) ((Targy0 *)(elem(targy0, x-1)->info))
#define aakadaly(x, a) ((Akadaly *)(elem(((Lista *)(elem(akadaly, x-1)->info)), a-1)->info))
#define aakadaly0(x) ((Akadaly0 *)(elem(akadaly0, x-1)->info))
#define aszereplo(x, a) ((Szereplo *)(elem(((Lista *)(elem(szereplo, x-1)->info)), a-1)->info))
#define aszereplo0(x) ((Szereplo0 *)(elem(szereplo0, x-1)->info))

/* Konstansok */

#define SZ_PARANCS 6
char *parancsok[SZ_PARANCS*2] = {
"k”rln‚zek", "n", "lelt rozok", "l", "v rok", "v",
"ment‚s", "m", "bet”lt‚s", "t", "kil‚p‚s", "b"};
#define SZ_IRANY 12
char *iranyok[SZ_IRANY*2] = {
"‚szak", "‚", "‚szakkelet", "‚k", "kelet", "k", "d‚lkelet", "dk", "d‚l", "d", "d‚lnyugat", "dny", "nyugat", "ny", "‚szaknyugat", "‚ny",
"fel", "f”l", "le", "", "ki", "", "be", ""};
#define MAX_SZOVEG 65534
#define MAX_HELYISEG 254
#define MAX_TARGY 2048
#define MAX_AKADALY 254
#define MAX_SZEREPLO 254
#define MAX_BEKEZDES 10
#define MAX_ALLAPOT 255
enum {T_INFO, T_HELYISEG, T_TARGY, T_AKADALY, T_SZEREPLO, T_VEGE};

/* V ltoz¢k */

Lista *szoveg = NULL, *helyiseg0 = NULL, *targy0 = NULL, *akadaly0 = NULL, *szereplo0 = NULL,
*helyiseg = NULL, *targy = NULL, *akadaly = NULL, *szereplo = NULL;
word szszoveg = 0, szhelyiseg = 0, sztargy = 0, szakadaly = 0, szszereplo = 0, szjatekos = 0;
byte jatekos = 0;
word cim = 0, bevezeto[MAX_BEKEZDES], epilogus[MAX_BEKEZDES];
char *parancs, *jatekfn, *mentesfn, *seged, *segeda;
time_t fajlido;
bool vanbev = 0, vege = 0, forras = 0, elso = 1, leptet = 1;

/* Fggv‚nyek */

void kezelp(EsemenyP *e, bool u);
void jatekosinfo(void);

/* Inicializ lja az adatszerkezeteket. */
void ujvilag(void)
{
	if (!(jatekfn = malloc(256))) hiba(U_MEM);
	if (!(mentesfn = malloc(256))) hiba(U_MEM);
	if (!(parancs = malloc(256))) hiba(U_MEM);
	if (!(seged = malloc(STRHOSSZ))) hiba(U_MEM);
	if (!(segeda = malloc(256))) hiba(U_MEM);
	if (!(segedb = malloc(256))) hiba(U_MEM);
	if (!(segedc = malloc(256))) hiba(U_MEM);
	*jatekfn = 0;
	*mentesfn = 0;
	*parancs = 0;
	*seged = 0;
	*segeda = 0;
	*segedb = 0;
	*segedc = 0;
	szszoveg = 0;
	szoveg = letrehoz(szoveg);
	if (!(szoveg->info = malloc(1))) hiba(U_MEM);
	strcpy(szoveg->info, "");
	memset(bevezeto, sizeof(bevezeto), 0);
	memset(epilogus, sizeof(epilogus), 0);
	helyiseg0 = letrehoz(helyiseg0);
	helyiseg = letrehoz(helyiseg);
	targy0 = letrehoz(targy0);
	targy = letrehoz(targy);
	akadaly0 = letrehoz(akadaly0);
	akadaly = letrehoz(akadaly);
	szereplo0 = letrehoz(szereplo0);
	szereplo = letrehoz(szereplo);
}

/* Felszabad¡tja a mem¢ri t. */
void vilagvege(void)
{
	free(jatekfn);
	free(mentesfn);
	free(parancs);
	free(seged);
	free(segeda);
	free(segedb);
	free(segedc);
	torol(szoveg);
	torol(helyiseg0);
	torol(helyiseg);
	torol(targy0);
	torol(targy);
	torol(akadaly0);
	torol(akadaly);
	torol(szereplo0);
	torol(szereplo);
}

/* Hozz fûzi s-hez egy t rgy nev‚t. */
void targynev(char *s, Lista *p0)
{
	switch (e_targy0->nevelo)
	{
		case 1:
		{
			strcat(s, "a");
			if (e_targy0->elotag)
			{
				if (mgh(*aszoveg(e_targy0->elotag))) strcat(s, "z");
			} else
			{
				if (mgh(*aszoveg(e_targy0->nev))) strcat(s, "z");
			}
			break;
		}
		case 2: strcat(s, "n‚mi"); break;
		case 3: strcat(s, "n‚h ny"); break;
		default: strcat(s, "egy"); break;
	}
	strcat(s, " ");
	if (e_targy0->elotag)
	{
		strcat(s, aszoveg(e_targy0->elotag));
	}
	strcat(s, aszoveg(e_targy0->nev));
}

/* Hozz fûzi s-hez egy szerepl‹ nev‚t, ha b 0, a nem egyedi k”znevek el‚ is hat rozott n‚vel‹t tesz. */
void szereplonev(char *s, Lista *p0, bool b)
{
	if (e_szereplo0->koznev)
	{
		if ((e_szereplo0->egyedi) || (!b))
		{
			if (*s) strcat(s, "a"); else strcat(s, "A");
			if (mgh(*(aszoveg(e_szereplo0->koznev)))) strcat(s, "z");
		}
		else
		{
			if (*s) strcat(s, "egy"); else strcat(s, "Egy");
		}
		strcat(s, " ");
		strcat(s, aszoveg(e_szereplo0->koznev));
	} else
	{
		strcat(s, aszoveg(e_szereplo0->nev));
	}
}

/* Meg llap¡tja, hogy s”t‚t van-e a helyis‚gben, ahol a j t‚kos tart¢zkodik. */
bool sotetvan(void)
{
	byte h = aszereplo0(jatekos)->hely;
	byte a = ahelyiseg0(h)->allapot;
	if (a)
	{
		if (ahelyiseg(h, a)->sotet)	return 1;
	} else
	{
		if (ahelyiseg0(h)->sotet)
			return 1;
	}
	return 0;
}

/* Meg llap¡tja, hogy s megegyezik-e az adott t rgy nev‚vel. */
bool egytargy(const char *s, Lista *p0)
{
	if (!strcmp(s, kisbetu(aszoveg(e_targy0->nev))))
	{
		return 1;
	}
	else
	{
		strcpy(segedc, aszoveg(e_targy0->elotag));
		strcat(segedc, aszoveg(e_targy0->nev));
		strcpy(segedc, kisbetu(segedc));
		if (!strcmp(s, segedc))
			return 1;
	}
	return 0;
}

/* Megv ltoztatja egy helyis‚g  llapot t. */
void ujha(byte x, byte a)
{
	byte i, j;
	Helyiseg0 *p = ahelyiseg0(x);
	if (a)
	{
		if ((i = ahelyiseg(x, a)->idozito) != 255)
			p->ido = i+1-(!i);
	} else
	{
		if ((i = p->idozito) != 255)
			p->ido = i+1-(!i);
	}
	if ((x == aszereplo0(jatekos)->hely) && (p->allapot != a) && ((i = ahelyiseg(x, p->allapot)->sotet) != (j = ahelyiseg(x, a)->sotet)) && ((!i) || (!j)))
	{
		p->allapot = a;
		korulnez();
	} else
	{
		p->allapot = a;
	}
}

/* Megv ltoztatja egy t rgy  llapot t. */
void ujta(byte x, byte a)
{
	byte i;
	Targy0 *p = atargy0(x);
	p->allapot = a;
	if (a)
	{
		if ((i = atargy(x, a)->idozito) != 255)
			p->ido = i+1-(!i);
		if (atargy(x, a)->helyiseg != 255)
			p->hely = atargy(x, a)->helyiseg;
		if (atargy(x, a)->szereplonel != 255)
			p->szer = atargy(x, a)->szereplonel;
	} else
	{
		if ((i = p->idozito) != 255)
			p->ido = i+1-(!i);
		if (p->helyiseg != 255)
			p->hely = p->helyiseg;
		if (p->szereplonel != 255)
			p->szer = p->szereplonel;
	}
}

/* Megv ltoztatja egy akad ly  llapot t. */
void ujaa(byte x, byte a)
{
	byte i;
	Akadaly0 *p = aakadaly0(x);
	p->allapot = a;
	if (a)
	{
		if ((i = aakadaly(x, a)->idozito) != 255)
			p->ido = i+1-(!i);
	} else
	{
		if ((i = p->idozito) != 255)
			p->ido = i+1-(!i);
	}
}

/* Megv ltoztatja egy szerepl‹  llapot t. */
void ujsa(byte x, byte a)
{
	word i, all, h = 0;
	Lista *p0, *pe1;
	Szereplo0 *p = aszereplo0(x);
	p->allapot = a;
	if (a)
	{
		h = p->hely;
		if ((i = aszereplo(x, a)->idozito) != 255)
			p->ido = i+1-(!i);
		if (aszereplo(x, a)->helyiseg != 255)
		{
			if ((p->hely == aszereplo0(jatekos)->hely) && (x != jatekos) && (aszereplo(x, a)->helyiseg))
			{
				if (sotetvan())
				{
					writeln("Valaki t vozik.");
				} else
				{
						*segeda = 0;
						szereplonev(segeda, elem(szereplo0, x-1), 1);
						strcat(segeda, " t vozik.");
						writeln(segeda);
				}
			}
			if (x == jatekos)
			{
				if (aszereplo(x, a)->helyiseg != p->hely)
				{
					p->hely = aszereplo(x, a)->helyiseg;
					if (p->hely) korulnez();
				}
			}
			else
			{
				p->hely = aszereplo(x, a)->helyiseg;
				if ((jatekos) && (p->hely == aszereplo0(jatekos)->hely))
				{
					if (sotetvan())
					{
						writeln("Valaki erre j”n.");
					} else
					{
						*segeda = 0;
						szereplonev(segeda, elem(szereplo0, x-1), 1);
						strcat(segeda, " j”n erre.");
						writeln(segeda);
					}
				}
			}
			p0 = szereplo0;
			for (i = 0; i < szszereplo; i++)
			{
				if (e_szereplo0->hely == p->hely)
				{
					if (all = e_szereplo0->allapot)
					{
						pe1 = aszereplo(i+1, all)->meglat;
					} else
					{
						pe1 = e_szereplo0->meglat;
					}
					while (pe1 && pe1->info)
					{
						if (x == e_esemenyp1->parameter)
						{
							kezelp(e_esemenyp1, (x == jatekos) || (i+1 == jatekos));
							break;
						}
						pe1 = pe1->kov;
					}
					if (a)
					{
						pe1 = aszereplo(x, a)->meglat;
					} else
					{
						pe1 = p->meglat;
					}
					while (pe1 && pe1->info)
					{
						if (i+1 == e_esemenyp1->parameter)
						{
							kezelp(e_esemenyp1, (x == jatekos) || (i+1 == jatekos));
							break;
						}
						pe1 = pe1->kov;
					}
				}
				p0 = p0->kov;
			}
		}
	} else
	{
		if ((i = p->idozito) != 255)
			p->ido = i+1-(!i);
		if (p->helyiseg != 255)
		{
			h = p->hely;
			if ((p->hely == aszereplo0(jatekos)->hely) && (x != jatekos) && (p->helyiseg))
			{
				if (sotetvan())
				{
					writeln("Valaki t vozik.");
				} else
				{
						*segeda = 0;
						szereplonev(segeda, elem(szereplo0, x-1), 1);
						strcat(segeda, " t vozik.");
						writeln(segeda);
				}
			}
			if (x == jatekos)
			{
				if (aszereplo0(x)->helyiseg != p->hely)
				{
					p->hely = aszereplo0(x)->helyiseg;
					if (p->hely) korulnez();
				}
			}
			else
			{
				p->hely = aszereplo0(x)->helyiseg;
				if ((jatekos) && (p->hely == aszereplo0(jatekos)->hely))
				{
					if (sotetvan())
					{
						writeln("Valaki erre j”n.");
					} else
					{
						*segeda = 0;
						szereplonev(segeda, elem(szereplo0, x-1), 1);
						strcat(segeda, " j”n erre.");
						writeln(segeda);
					}
				}
			}
			p0 = szereplo0;
			for (i = 0; i < szszereplo; i++)
			{
				if (e_szereplo0->hely == p->hely)
				{
					if (all = e_szereplo0->allapot)
					{
						pe1 = aszereplo(i+1, all)->meglat;
					} else
					{
						pe1 = e_szereplo0->meglat;
					}
					while (pe1 && pe1->info)
					{
						if (x == e_esemenyp1->parameter)
						{
							kezelp(e_esemenyp1, (x == jatekos) || (i+1 == jatekos));
							break;
						}
						pe1 = pe1->kov;
					}
					if (a)
					{
						pe1 = aszereplo(x, a)->meglat;
					} else
					{
						pe1 = p->meglat;
					}
					while (pe1 && pe1->info)
					{
						if (i+1 == e_esemenyp1->parameter)
						{
							kezelp(e_esemenyp1, (x == jatekos) || (i+1 == jatekos));
							break;
						}
						pe1 = pe1->kov;
					}
				}
				p0 = p0->kov;
			}
		}
	}
	/* Ha egy ir ny¡that¢ szerepl‹ eltûnik, eldobja a t rgyait. */
	if ((!(p->hely)) && (p->iranyithato))
	{
		p0 = targy0;
		for (i = 0; i < sztargy; i++)
		{
			if ((e_targy0->szer) && (e_targy0->hely == x))
			{
				e_targy0->szer = 0;
				e_targy0->hely = h;
			}
			p0 = p0->kov;
		}
	}
	/* Ha a j t‚kos tûnik el, j t‚kost v ltunk. */
	if ((!(p->hely)) && (x == jatekos))
	{
		p0 = szereplo0;
		for (i = 0; i < szszereplo; i++)
		{
			if (e_szereplo0->iranyithato)
			{
				jatekos = i+1;
				jatekosinfo();
				break;
			}
			p0 = p0->kov;
		}
	}
}

/* V‚grehajt egy esem‚nykezel‹t. Ha u 0, nem ¡rja ki az zenetet. */
void kezel(Esemeny *e, bool u)
{
	word i;
	byte j;
	if ((u) && (e->uzenet)) writeln(aszoveg(e->uzenet));
	for (i = 0; i < e->szallapot; i++)
	{
		switch (e->allapot[i].tipus)
		{
			case T_HELYISEG:
			{
				ujha(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_TARGY:
			{
				ujta(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_AKADALY:
			{
				ujaa(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_SZEREPLO:
			{
				ujsa(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_VEGE:
			{
				leptet = 0;
				if (!(e->allapot[i].allapot))
				{
					j = 0;
					while (epilogus[j])
					{
						poz = 0;
						writeln(aszoveg(epilogus[j]));
						if ((j < MAX_BEKEZDES-1) && (epilogus[j+1]))
						{
							write("<Tov bb>");
						}
						getchar();
						fflush(stdin);
						j++;
					}
				}
				vege = 1;
				break;
			}
		}
	}
}

/* V‚grehajt egy param‚teres esem‚nykezel‹t. Ha u 0, nem ¡rja ki az zenetet. */
void kezelp(EsemenyP *e, bool u)
{
	word i;
	byte j;
	if ((u) && (e->uzenet)) writeln(aszoveg(e->uzenet));
	for (i = 0; i < e->szallapot; i++)
	{
		switch (e->allapot[i].tipus)
		{
			case T_HELYISEG:
			{
				ujha(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_TARGY:
			{
				ujta(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_AKADALY:
			{
				ujaa(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_SZEREPLO:
			{
				ujsa(e->allapot[i].sorszam, e->allapot[i].allapot);
				break;
			}
			case T_VEGE:
			{
				leptet = 0;
				if (!(e->allapot[i].allapot))
				{
					j = 0;
					while (epilogus[j])
					{
						poz = 0;
						writeln(aszoveg(epilogus[j]));
						if ((j < MAX_BEKEZDES-1) && (epilogus[j+1]))
						{
							write("<Tov bb>");
						}
						getchar();
						fflush(stdin);
						j++;
					}
				}
				vege = 1;
				break;
			}
		}
	}
}
