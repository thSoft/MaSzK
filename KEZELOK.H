/* MaSzK */
/* Kezel‹k */

#define U_FAJLNEV "F jln‚v: "
#define U_ROSSZM "Ez a j t‚k llapot nem ehhez a kalandj t‚khoz tartozik!"
#define U_FK "A megadott f jl nem MaSzK forr sf jl vagy kalandj t‚k-f jl!"
#define U_M "A megadott f jl nem MaSzK j t‚k llapot-f jl!"

word szt;

/* A k”rln‚z‚s kezel‹je. */
void korulnez(void)
{
	word h, a, i;
	char *p, *t;
	Lista *p0 = targy0;
	h = aszereplo0(jatekos)->hely;
	a = ahelyiseg0(h)->allapot;
	if (a)
	{
		if (ahelyiseg(h, a)->sotet)
		{
			writeln("Egy s”t‚t helyis‚gben vagy.");
			return;
		}
		if (ahelyiseg(h, a)->leiras)
			writeln(aszoveg(ahelyiseg(h, a)->leiras));
		else
		{
			write("Tart¢zkod sod helye: ");
			write(aszoveg(ahelyiseg0(h)->nev));
			writeln(".");
		}
	}
	else
	{
		if (ahelyiseg0(h)->sotet)
		{
			writeln("Egy s”t‚t helyis‚gben vagy.");
			return;
		}
		if (ahelyiseg0(h)->leiras)
			writeln(aszoveg(ahelyiseg0(h)->leiras));
		else
		{
			write("Tart¢zkod sod helye: ");
			write(aszoveg(ahelyiseg0(h)->nev));
			writeln(".");
		}
	}
	strcpy(seged, "Itt van");
	for (i = 0; i < sztargy; i++)
	{
		if ((!(e_targy0->szer)) && (e_targy0->hely == aszereplo0(jatekos)->hely) && (!(e_targy0->rogzitett)))
		{
			strcat(seged, " ");
			targynev(seged, p0);
			strcat(seged, ",");
		}
		p0 = p0->kov;
	}
	if (strlen(seged) > 7)
	{
		seged[strlen(seged)-1] = '.';
		if (p = strrchr(seged, ','))
		{
			if (!(t = malloc(strlen(seged)-(p-seged)))) hiba(U_MEM);
			strcpy(t, &(p[1]));
			*p = 0;
			strcat(seged, " ‚s");
			strcat(seged, t);
			free(t);
		}
		writeln(seged);
	}
	strcpy(seged, "Itt van");
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if ((e_szereplo0->hely == aszereplo0(jatekos)->hely) && (i+1 != jatekos))
		{
			strcat(seged, " ");
			szereplonev(seged, p0, 1);
			strcat(seged, ",");
		}
		p0 = p0->kov;
	}
	if (strlen(seged) > 7)
	{
		seged[strlen(seged)-1] = '.';
		if (p = strrchr(seged, ','))
		{
			if (!(t = malloc(strlen(seged)-(p-seged)))) hiba(U_MEM);
			strcpy(t, &(p[1]));
			*p = 0;
			strcat(seged, " ‚s");
			strcat(seged, t);
			free(t);
		}
		writeln(seged);
	}
}

/* A lelt roz s kezel‹je. */
void leltaroz(void)
{
	word i;
	bool j;
	char *p, *t;
	Lista *p0 = targy0;
	szt = 1;
	strcpy(seged, "N lad van");
	for (i = 0; i < sztargy; i++)
	{
		j = ((e_targy0->szer) && (e_targy0->hely == jatekos));
		if (j)
		{
			strcat(seged, " ");
			targynev(seged, p0);
			strcat(seged, ",");
		}
		p0 = p0->kov;
	}
	if (strlen(seged) == 9)
	{
		writeln("Nincs n lad semmi.");
		szt = 0;
	}
	else
	{
		seged[strlen(seged)-1] = '.';
		if (p = strrchr(seged, ','))
		{
			if (!(t = malloc(strlen(seged)-(p-seged)))) hiba(U_MEM);
			strcpy(t, &(p[1]));
			*p = 0;
			strcat(seged, " ‚s");
			strcat(seged, t);
			free(t);
		}
		writeln(seged);
	}
}

/* A v rakoz s kezel‹je. */
void var(void)
{
	writeln("M£lik az id‹...");
}

/* A ment‚s kezel‹je. */
void mentes(void)
{
	write(U_FAJLNEV);
	gets(segeda);
	fflush(stdin);
	poz = 0;
	if (*segeda)
	{
		if (elment(segeda))
		{
			writeln(U_FAJL);
		}
		else
		{
			strcpy(mentesfn, segeda);
			elmentb();
		}
	}
}

/* A bet”lt‚s kezel‹je. */
void betoltes(void)
{
	write(U_FAJLNEV);
	gets(segeda);
	fflush(stdin);
	poz = 0;
	if (*segeda)
	{
		switch (betoltm(segeda))
		{
			case -1: writeln(U_FAJL); break;
			case -2: writeln(U_ROSSZM); break;
			case -3: writeln(U_M); break;
		}
	}
}

/* A kil‚p‚s kezel‹je. */
void kilepes(void)
{
	vege = kerdes("Biztosan ki akarsz l‚pni?");
}

typedef void (*Kezelo)(void);
Kezelo pk[SZ_PARANCS] = {korulnez, leltaroz, var, mentes, betoltes, kilepes};

/* A mozg s kezel‹je. */
void mozog(int irany)
{
	byte start, cel, all;
	word i;
	Lista *p0, *pe1;
	bool siker = 1;
	*seged = 0;
	start = aszereplo0(jatekos)->hely;
	cel = ahelyiseg0(start)->kijaratok[irany];
	if (!cel)
	{
		writeln("Nem mehetsz abba az ir nyba.");
		return;
	}
	p0 = akadaly0;
	for (i = 0; i < szakadaly; i++)
	{
		if (((e_akadaly0->egyik == start) && (e_akadaly0->masik == cel)) || ((e_akadaly0->egyik == cel) && (e_akadaly0->masik == start)))
		{
			if (e_akadaly0->allapot)
			{
				siker = aakadaly(i+1, e_akadaly0->allapot)->jarhato;
			}
			else
			{
				siker = e_akadaly0->jarhato;
			}
			if (!siker) break;
		}
		p0 = p0->kov;
	}
	if (!siker)
	{
		write("Egy ");
		write(aszoveg(e_akadaly0->nev));
		writeln("  llja utadat.");
		return;
	}
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if ((e_szereplo0->hely == aszereplo0(jatekos)->hely) && (i+1 != jatekos))
		{
			if (e_szereplo0->allapot)
			{
				siker = (aszereplo(i, e_szereplo0->allapot)->irany != irany+1);
			}
			else
			{
				siker = (e_szereplo0->irany != irany+1);
			}
			if (!siker) break;
		}
		p0 = p0->kov;
	}
	if (!siker)
	{
		szereplonev(seged, p0, 0);
		strcat(seged, " utadat  llja.");
		writeln(seged);
		return;
	}
	if (i = ahelyiseg0(start)->allapot)
	{
		kezel(&(ahelyiseg(start, i)->kimegy), 1);
	} else
	{
		kezel(&(ahelyiseg0(start)->kimegy), 1);
	}
	aszereplo0(jatekos)->hely = cel;
	korulnez();
	if (i = ahelyiseg0(cel)->allapot)
	{
		kezel(&(ahelyiseg(cel, i)->belep), 1);
	} else
	{
		kezel(&(ahelyiseg0(cel)->belep), 1);
	}
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if (e_szereplo0->hely == aszereplo0(jatekos)->hely)
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
				if (jatekos == e_esemenyp1->parameter)
				{
					kezelp(e_esemenyp1, 1);
					break;
				}
				pe1 = pe1->kov;
			}
			if (all = aszereplo0(jatekos)->allapot)
			{
				pe1 = aszereplo(jatekos, all)->meglat;
			} else
			{
				pe1 = aszereplo0(jatekos)->meglat;
			}
			while (pe1 && pe1->info)
			{
				if (i+1 == e_esemenyp1->parameter)
				{
					kezelp(e_esemenyp1, 1);
					break;
				}
				pe1 = pe1->kov;
			}
		}
		p0 = p0->kov;
	}
}
