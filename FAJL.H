/* MaSzK */
/* BetîltÇs Çs mentÇs */

#define S_MF "[mf]"
#define S_MK "[mk]"
#define S_MM "[mm]"
#define S_MB "[mb]"
#define S_MBFN "maszk.mbf"
#define S_JATEK "jatek=\""
#define S_MENTES "mentes=\""
#define S_H "helyisÇg"
#define S_T "t†rgy"
#define S_A "akad†ly"
#define S_S "szereplã"
#define S_SZ "szîveg"
#define S_ALL "†llapot"
#define S_CIM "cim"
#define S_BEV "bevezeto"
#define S_EPI "epilogus"
#define S_NEV "nev"
#define S_LEIRAS "leiras"
#define S_SOTET "sotet"
#define S_KIJARAT "kijaratok"
#define S_HELY "helyiseg"
#define S_SZER "szereplonel"
#define S_ELO "elotag"
#define S_ROGZ "rogzitett"
#define S_NEVELO "nevelo"
#define S_JARHATO "jarhato"
#define S_EGYIK "egyik"
#define S_MASIK "masik"
#define S_IRANY "irany"
#define S_KOZ "koznev"
#define S_EGYEDI "egyedi"
#define S_IR "iranyithato"
#define S_IDO "idozito"
#define S_VIZSGAL "vizsgal"
#define S_LEJAR "lejar"
#define S_BE "belep"
#define S_KI "kimegy"
#define S_FELVESZ "felvesz"
#define S_LETESZ "letesz"
#define S_LEP "lep"
#define S_IRANYIT "iranyit"
#define S_LAT "meglat"
#define S_AKCIO "akcio"
#define S_ESZKOZ "eszkoz"
#define S_AD "ad"
#define S_MUTAT "mutat"
#define S_BESZEL "beszel"
#define U_TOLTES " betîltÇse..."
#define U_ROSSZSOR "Hib†s sor! Helyes alak: pozit°v egÇsz sz†m = \"szîveg\""
#define U_ROSSZSOR2 "Hib†s sor! Helyes alak: nÇv = ÇrtÇkek"
#define U_HOSSZU "T£l hossz£ a szîveg!"
#define U_SOKPARAM "T£l sok paramÇter!"
#define U_KEVESPARAM "T£l kevÇs paramÇter!"
#define U_MENTESH "Nem tudtam elmenteni a kÇsz kalandj†tÇk-f†jlt!"
#define U_SZAKASZ "M†r volt ilyen szakasz!"
#define U_ROSSZTUL "Ismeretlen tulajdons†g!"
#define U_ROSSZALL "Helytelen †llapotv†ltoz†s!"
#define U_NINCSJ "Nincsen ir†ny°that¢ j†tÇkos!"
#define U_ROSSZP "A paramÇter csak nemnegat°v egÇsz sz†m lehet!"
#define U_PS "A program parancssori paramÇterÇben add meg a betîltendã kalandj†tÇk-f†jl nevÇt!"

/* Kiszedi a megjegyzÇseket Çs Åres karaktereket egy stringbãl. */
void tisztit(char *s)
{
	char *a;
	int i;
	if (s[strlen(s)-1] == '\n')
		s[strlen(s)-1] = 0;
	if (!(*s)) return;
	if (a = strchr(s, ';'))
		*a = 0;
	if (!(*s)) return;
	i = 0;
	while ((s[i]) && (s[i] != '"'))
	{
		if ((s[i] == ' ') || (s[i] == '\t'))
		{
			while ((s[i]) && ((s[i] == ' ') || (s[i] == '\t')))
				strcpy(&s[i], &s[i+1]);
		}
		if (s[i] == '"') break;
		i++;
	}
}

/* SzÇtszed egy szîveg-sz†m stringet,
pl. ha s "abc8def32", akkor r "abc8def", n pedig 32 lesz. */
void szetszed(const char *s, char *r, word *n)
{
	int i;
	char *a;
	i = strlen(s)-1;
	while ((i >= 0) && (isdigit(s[i])))
		i--;
	i++;
	if (!s[i])
	{
		strcpy(r, s);
		r[i] = 0;
		*n = 0;
		return;
	}
	if (!(a = malloc(strlen(s)-i+1))) hiba(U_MEM);
	strncpy(r, s, i);
	r[i] = 0;
	strcpy(a, &s[i]);
	a[strlen(s)-i] = 0;
	*n = atoi(a);
	free(a);
}

/* Feldolgoz egy †llapotv†ltoz†st (t°pus sorsz†m / £j †llapot). */
int ujallapot(const char *s, Allapot *a)
{
	if (count(s, '/') != 1)
		return -1;
	strcpy(segeda, &(strchr(s, '/')[1]));
	a->allapot = atoi(segeda);
	strchr(s, '/')[0] = 0;
	szetszed(s, segeda, &(a->sorszam));
	switch (segeda[0])
	{
		case 'h':
		{
			a->tipus = T_HELYISEG;
			break;
		}
		case 't':
		{
			a->tipus = T_TARGY;
			break;
		}
		case 'a':
		{
			a->tipus = T_AKADALY;
			break;
		}
		case 's': {
			a->tipus = T_SZEREPLO;
			break;
		}
		case 'v': {
			a->tipus = T_VEGE;
			break;
		}
		default: return -1;
	}
	return 0;
}

/* Jelzi, hogy a hivatkoz†s ÇrvÇnytelen. */
void hivhiba(const char *s, word x)
{
	write("Hiba: A(z) ");
	write(itostr(x));
	write(". ");
	write(s);
	write(" nem lÇtezik");
	writeln("!");
	hiba("");
}

/* Jelzi, hogy a megadott objektumnak nem lÇtezik a megadott †llapota. */
void allhiba(const char *s, word x, byte a)
{
	write("Hiba: A(z) ");
	write(itostr(x));
	write(". ");
	write(s);
	write(" nem lÇtezik");
	write(" a(z) ");
	write(itostr(a));
	writeln(". †llapota!");
	hiba("");
}

void tulhiba(const char *s, const char *t, word x)
{
	write("Hiba: A(z) ");
	write(itostr(x));
	write(". ");
	write(s);
	write(" nincs ");
	write(t);
	writeln("!");
	hiba("");
}

/* Inicializ†l egy esemÇnyt a darab †llapottal. */
void esemenyinit(Esemeny *e, byte a)
{
	if (a)
	{
		if (!(e->allapot = malloc(sizeof(Allapot)*a))) hiba(U_MEM);
		memset(e->allapot, 0, sizeof(Allapot)*a);
	}
	e->szallapot = a;
}

/* Inicializ†l egy paramÇteres esemÇnyt a darab †llapottal. */
void esemenypinit(EsemenyP *e, byte a)
{
	if (a)
	{
		if (!(e->allapot = malloc(sizeof(Allapot)*a))) hiba(U_MEM);
		memset(e->allapot, 0, sizeof(Allapot)*a);
	}
	e->szallapot = a;
}

/* Elment egy esemÇnyt. */
void esemenyment(Esemeny *e, FILE *f)
{
	byte i;
	fwrite(&(e->uzenet), 2, 1, f);
	fwrite(&(e->szallapot), 1, 1, f);
	if (e->szallapot)
	{
		for (i = 0; i < e->szallapot; i++)
		{
			switch (e->allapot[i].tipus)
			{
				case T_HELYISEG:
				{
					if (e->allapot[i].sorszam > szhelyiseg)
					{
						fclose(f);
						hivhiba(S_H, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Helyiseg0 *)(elem(helyiseg0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("helyisÇgnek", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_TARGY:
				{
					if (e->allapot[i].sorszam > sztargy)
					{
						fclose(f);
						hivhiba(S_T, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Targy0 *)(elem(targy0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("t†rgynak", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_AKADALY:
				{
					if (e->allapot[i].sorszam > szakadaly)
					{
						fclose(f);
						hivhiba(S_A, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Akadaly0 *)(elem(akadaly0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("akad†lynak", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_SZEREPLO:
				{
					if (e->allapot[i].sorszam > szszereplo)
					{
						fclose(f);
						hivhiba(S_S, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Szereplo0 *)(elem(szereplo0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("szereplãnek", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
			}
			fwrite(&(e->allapot[i].tipus), 1, 1, f);
			fwrite(&(e->allapot[i].sorszam), 2, 1, f);
			fwrite(&(e->allapot[i].allapot), 1, 1, f);
		}
	}
}

/* Elment egy paramÇteres esemÇnyt. */
void esemenypment(EsemenyP *e, FILE *f)
{
	byte i;
	fwrite(&(e->parameter), 2, 1, f);
	fwrite(&(e->uzenet), 2, 1, f);
	fwrite(&(e->szallapot), 1, 1, f);
	if (e->szallapot)
	{
		for (i = 0; i < e->szallapot; i++)
		{
			switch (e->allapot[i].tipus)
			{
				case T_HELYISEG:
				{
					if (e->allapot[i].sorszam > szhelyiseg)
					{
						fclose(f);
						hivhiba(S_H, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Helyiseg0 *)(elem(helyiseg0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("helyisÇgnek", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_TARGY:
				{
					if (e->allapot[i].sorszam > sztargy)
					{
						fclose(f);
						hivhiba(S_T, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Targy0 *)(elem(targy0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("t†rgynak", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_AKADALY:
				{
					if (e->allapot[i].sorszam > szakadaly)
					{
						fclose(f);
						hivhiba(S_A, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Akadaly0 *)(elem(akadaly0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("akad†lynak", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
				case T_SZEREPLO:
				{
					if (e->allapot[i].sorszam > szszereplo)
					{
						fclose(f);
						hivhiba(S_S, e->allapot[i].sorszam);
					}
					if (e->allapot[i].allapot > ((Szereplo0 *)(elem(szereplo0, e->allapot[i].sorszam-1))->info)->szallapot)
					{
						fclose(f);
						allhiba("szereplãnek", e->allapot[i].sorszam, e->allapot[i].allapot);
					}
					break;
				}
			}
			fwrite(&(e->allapot[i].tipus), 1, 1, f);
			fwrite(&(e->allapot[i].sorszam), 2, 1, f);
			fwrite(&(e->allapot[i].allapot), 1, 1, f);
		}
	}
}

/* Betîlt egy esemÇnyt. */
void esemenytolt(Esemeny *e, FILE *f)
{
	byte i;
	fread(&(e->uzenet), 2, 1, f);
	fread(&(e->szallapot), 1, 1, f);
	if (e->szallapot)
	{
		esemenyinit(e, e->szallapot);
		for (i = 0; i < e->szallapot; i++)
		{
			fread(&(e->allapot[i].tipus), 1, 1, f);
			fread(&(e->allapot[i].sorszam), 2, 1, f);
			fread(&(e->allapot[i].allapot), 1, 1, f);
		}
	}
}

/* Betîlt egy paramÇteres esemÇnyt. */
void esemenyptolt(EsemenyP *e, FILE *f)
{
	byte i;
	fread(&(e->parameter), 2, 1, f);
	fread(&(e->uzenet), 2, 1, f);
	fread(&(e->szallapot), 1, 1, f);
	if (e->szallapot)
	{
		esemenypinit(e, e->szallapot);
		for (i = 0; i < e->szallapot; i++)
		{
			fread(&(e->allapot[i].tipus), 1, 1, f);
			fread(&(e->allapot[i].sorszam), 2, 1, f);
			fread(&(e->allapot[i].allapot), 1, 1, f);
		}
	}
}

/* Hib†t jelez az l. sorban. */
int fajlhiba(const char *s, dword l)
{
	if (*s)
	{
		write("Hiba: ");
		write(s);
	}
	write(" (");
	write(itostr(l));
	writeln(". sor)");
	return -1;
}

/* Jelzi, hogy a f†jlban az x. objektumnak kell kîvetkeznie. */
int sorszamhiba(const char *s, long x, long l)
{
	if (!x) x = 1;
	write("Hiba: ");
	write("Itt a(z) ");
	write(itostr(x));
	write(". ");
	write(s);
	write(" kell kîvetkeznie!");
	return fajlhiba("", l);
}

/* Jelzi, hogy t£l sok objektum van megadva. */
int maxhiba(const char *s, long x, long l)
{
	write("Hiba: ");
	write("Legfeljebb ");
	write(itostr(x));
	write(". ");
	write(s);
	write(" lehet!");
	return fajlhiba("", l);
}

/* Jelzi, hogy a megadott tulajdons†g nem v†ltoz¢. */
int vhiba(const char *s, long l)
{
	write("Hiba: A(z) ");
	write(s);
	write(" tulajdons†g nem v†ltoz¢!");
	return fajlhiba("", l);
}

/* Jelzi, hogy a megadott objektum nem lÇtezik. */
int hhiba(const char *s, long l)
{
	write("Hiba: ");
	write(s);
	write("!");
	return fajlhiba("", l);
}

/* Jelzi, hogy nincs ilyen objektum a j†tÇkban. */
int nhiba(const char *s)
{
	write("Hiba: ");
	write("Nincsen ");
	write(s);
	writeln(" a j†tÇkban!");
	return -1;
}

/* Leford°t Çs betîlt egy MaSzK forr†sf†jlt, a kimenet az fn nev˚ f†jlban lesz. */
int forrast(FILE *f, char *fn)
{
	FILE *f2;
	char *s, *t, *v;
	dword i, j, h, l = 1, e, he, ssz = 0, all, cc;
	word x;
	byte mit = 0;
	Lista *p, *p0, *pa, *pe1, *pe2, *pe3, *pe4, *pe5, *pe6;
	/* A szîvegrÇsz feldolgoz†sa */
	if (!(s = malloc(512))) hiba(U_MEM);
	if (!(t = malloc(256))) hiba(U_MEM);
	if (!(v = malloc(256))) hiba(U_MEM);
	szszoveg = 1;
	p = szoveg;
	while (!feof(f))
	{
		if (fgets(s, 512, f))
		{
			l++;
			tisztit(s);
			if (!(*s)) continue;
			if (*s == '[')
			{
				strlwr(s);
				if (strcmp(s, "[info]"))
					return fajlhiba("Itt az [info] szakasznak kell kîvetkeznie!", l);
				else
					break;
			}
			if (!strchr(s, '='))
				return fajlhiba(U_ROSSZSOR, l);
			i = 0;
			while ((s[i]) && (s[i] != '='))
			{
				t[i] = s[i];
				i++;
			}
			t[i] = 0;
			if (!(x = atoi(t)))
				return fajlhiba(U_ROSSZSOR, l);
			if (x != szszoveg)
				return sorszamhiba("szîvegnek", szszoveg, l);
			if (x > MAX_SZOVEG)
				return maxhiba(S_SZ, MAX_SZOVEG, l);
			i++;
			if (s[i] != '"')
				return fajlhiba(U_ROSSZSOR, l);
			else
			{
				h = 0;
				i++;
				while (1)
				{
					while ((s[i]) && (s[i] != '"'))
					{
						if ((s[i] == '\\') && (s[i+1]))
						{
							switch (s[i+1])
							{
								case '"': seged[h] = '"'; i++; break;
								case 'n': seged[h] = '\n'; i++; break;
								case '\\': seged[h] = '\\'; i++;
							}
						}
						else
							seged[h] = s[i];
						i++;
						h++;
						if (h >= STRHOSSZ)
							return fajlhiba(U_HOSSZU, l);
					}
					if (s[i] == '"')
					{
						seged[h] = 0;
						p = beszur(p);
						if (!(p->info = (char *)malloc(h+1))) hiba(U_MEM);
						strcpy(p->info, seged);
						szszoveg++;
						break;
					}
					else
					{
						if (!fgets(s, 512, f))
							return fajlhiba("A f†jl v†ratlanul Çrt vÇget!", l);
						if (s[strlen(s)-1] == '\n')
							s[strlen(s)-1] = 0;
						l++;
						seged[h] = ' ';
						h++;
						if (h >= STRHOSSZ)
							return fajlhiba(U_HOSSZU, l);
						i = 0;
					}
				}
			}
		}
	}
	szszoveg--;
	/* A j†tÇk egyÇb adatainak feldolgoz†sa */
	while (!feof(f))
	{
		if (fgets(s, 512, f))
		{
			l++;
			tisztit(s);
			strlwr(s);
			if (!(*s)) continue;
			if (*s == '[')
			{
				switch (mit)
				{
					case T_HELYISEG:
					{
						if (!ssz) return nhiba(S_H);
						szhelyiseg = ssz;
						if (e_helyiseg0) e_helyiseg0->szallapot = all;
						break;
					}
					case T_TARGY:
					{
						if (!ssz) return nhiba(S_T);
						sztargy = ssz;
						if (e_targy0) e_targy0->szallapot = all;
						break;
					}
					case T_AKADALY:
					{
						if (!ssz) return nhiba(S_A);
						szakadaly = ssz;
						if (e_targy0) e_akadaly0->szallapot = all;
						break;
					}
					case T_SZEREPLO:
					{
						if (!ssz) return nhiba(S_S);
						szszereplo = ssz;
						if (e_szereplo0) e_szereplo0->szallapot = all;
						break;
					}
				}
				ssz = 0;
				if (!strcmp(s, "[helyisegek]"))
				{
					if (szhelyiseg > 0) return fajlhiba(U_SZAKASZ, l);
					mit = T_HELYISEG;
					p0 = helyiseg0;
					p = helyiseg;
				} else
				if (!strcmp(s, "[targyak]"))
				{
					if (sztargy > 0) return fajlhiba(U_SZAKASZ, l);
					mit = T_TARGY;
					p0 = targy0;
					p = targy;
				} else
				if (!strcmp(s, "[akadalyok]"))
				{
					if (szakadaly > 0) return fajlhiba(U_SZAKASZ, l);
					mit = T_AKADALY;
					p0 = akadaly0;
					p = akadaly;
				} else
				if (!strcmp(s, "[szereplok]"))
				{
					if (szszereplo > 0) return fajlhiba(U_SZAKASZ, l);
					mit = T_SZEREPLO;
					p0 = szereplo0;
					p = szereplo;
				} else
					return fajlhiba("Ismeretlen szakasznÇv!", l);
				continue;
			}
			if (*s == ':')
			{
				ssz++;
				strcpy(s, &s[1]);
				if ((!ssz) || (atoi(s) != ssz))
					return sorszamhiba("elemnek", ssz, l);
				switch (mit)
				{
					case T_HELYISEG:
					{
						if (ssz > MAX_HELYISEG)
							return maxhiba(S_H, MAX_HELYISEG, l);
						if (ssz > 1)
						{
							e_helyiseg0->szallapot = all;
							p0 = beszur(p0);
							p = beszur(p);
						}
						if (!(p0->info = (Helyiseg0 *)malloc(sizeof(Helyiseg0)))) hiba(U_MEM);
						e_helyiseg0->allapot = 0;
						e_helyiseg0->ido = 0;
						e_helyiseg0->idozito = 0;
						e_helyiseg0->nev = 0;
						e_helyiseg0->leiras = 0;
						e_helyiseg0->sotet = 0;
						memset(e_helyiseg0->kijaratok, 0, 12);
						e_helyiseg0->lejar.szallapot = 0;
						e_helyiseg0->lejar.parameter = 0;
						e_helyiseg0->lejar.uzenet = 0;
						e_helyiseg0->belep.szallapot = 0;
						e_helyiseg0->belep.uzenet = 0;
						e_helyiseg0->kimegy.szallapot = 0;
						e_helyiseg0->kimegy.uzenet = 0;
						break;
					}
					case T_TARGY:
					{
						if (ssz > MAX_TARGY)
							return maxhiba(S_T, MAX_TARGY, l);
						if (ssz > 1)
						{
							e_targy0->szallapot = all;
							p0 = beszur(p0);
							p = beszur(p);
						}
						if (!(p0->info = (Targy0 *)malloc(sizeof(Targy0)))) hiba(U_MEM);
						e_targy0->allapot = 0;
						e_targy0->idozito = 0;
						e_targy0->nev = 0;
						e_targy0->leiras = 0;
						e_targy0->elotag = 0;
						e_targy0->helyiseg = 0;
						e_targy0->szereplonel = 0;
						e_targy0->hely = 0;
						e_targy0->szer = 0;
						e_targy0->ido = 0;
						e_targy0->rogzitett = 0;
						e_targy0->nevelo = 0;
						e_targy0->vizsgal.szallapot = 0;
						e_targy0->vizsgal.uzenet = 0;
						e_targy0->lejar.szallapot = 0;
						e_targy0->lejar.parameter = 0;
						e_targy0->lejar.uzenet = 0;
						e_targy0->felvesz.szallapot = 0;
						e_targy0->felvesz.uzenet = 0;
						e_targy0->letesz.szallapot = 0;
						e_targy0->letesz.uzenet = 0;
						e_targy0->szakcio = 0;
						e_targy0->szeszkoz = 0;
						e_targy0->akcio = NULL;
						e_targy0->eszkoz = NULL;
						break;
					}
					case T_AKADALY:
					{
						if (ssz > MAX_AKADALY)
							return maxhiba(S_A, MAX_AKADALY, l);
						if (ssz > 1)
						{
							e_akadaly0->szallapot = all;
							p0 = beszur(p0);
							p = beszur(p);
						}
						if (!(p0->info = (Akadaly0 *)malloc(sizeof(Akadaly0)))) hiba(U_MEM);
						e_akadaly0->allapot = 0;
						e_akadaly0->idozito = 0;
						e_akadaly0->ido = 0;
						e_akadaly0->nev = 0;
						e_akadaly0->leiras = 0;
						e_akadaly0->egyik = 0;
						e_akadaly0->masik = 0;
						e_akadaly0->jarhato = 0;
						e_akadaly0->vizsgal.szallapot = 0;
						e_akadaly0->vizsgal.uzenet = 0;
						e_akadaly0->lejar.szallapot = 0;
						e_akadaly0->lejar.parameter = 0;
						e_akadaly0->lejar.uzenet = 0;
						e_akadaly0->szakcio = 0;
						e_akadaly0->szeszkoz = 0;
						e_akadaly0->akcio = NULL;
						e_akadaly0->eszkoz = NULL;
						break;
					}
					case T_SZEREPLO:
					{
						if (ssz > MAX_SZEREPLO)
							return maxhiba(S_S, MAX_SZEREPLO, l);
						if (ssz > 1)
						{
							e_szereplo0->szallapot = all;
							p0 = beszur(p0);
							p = beszur(p);
						}
						if (!(p0->info = (Szereplo0 *)malloc(sizeof(Szereplo0)))) hiba(U_MEM);
						e_szereplo0->allapot = 0;
						e_szereplo0->idozito = 0;
						e_szereplo0->ido = 0;
						e_szereplo0->hely = 0;
						e_szereplo0->nev = 0;
						e_szereplo0->leiras = 0;
						e_szereplo0->koznev = 0;
						e_szereplo0->egyedi = 0;
						e_szereplo0->helyiseg = 0;
						e_szereplo0->irany = 0;
						e_szereplo0->iranyithato = 0;
						e_szereplo0->vizsgal.szallapot = 0;
						e_szereplo0->vizsgal.uzenet = 0;
						e_szereplo0->lejar.szallapot = 0;
						e_szereplo0->lejar.parameter = 0;
						e_szereplo0->lejar.uzenet = 0;
						e_szereplo0->lep.szallapot = 0;
						e_szereplo0->lep.parameter = 0;
						e_szereplo0->lep.uzenet = 0;
						e_szereplo0->iranyit.szallapot = 0;
						e_szereplo0->iranyit.uzenet = 0;
						e_szereplo0->szakcio = 0;
						e_szereplo0->szeszkoz = 0;
						e_szereplo0->szmeglat = 0;
						e_szereplo0->szbeszel = 0;
						e_szereplo0->szad = 0;
						e_szereplo0->szmutat = 0;
						e_szereplo0->akcio = NULL;
						e_szereplo0->eszkoz = NULL;
						e_szereplo0->meglat = NULL;
						e_szereplo0->beszel = NULL;
						e_szereplo0->ad = NULL;
						e_szereplo0->mutat = NULL;
						break;
					}
				}
				all = 0;
				continue;
			}
			if (*s == '/')
			{
				all++;
				strcpy(s, &s[1]);
				if (!strcmp(s, "0"))
					return fajlhiba("A 0. †llapotot nem kell kÅlîn jelîlni!", l);
				if (atoi(s) != all)
					return sorszamhiba("†llapotnak", ssz, l);
				if (all > MAX_ALLAPOT)
					return maxhiba(S_ALL, all, l);
				switch (mit)
				{
					case T_HELYISEG:
					{
						if (all == 1)
						{
							p->info = letrehoz(e_helyiseg);
							pa = p->info;
						} else
						{
							pa = beszur(pa);
						}
						if (!(pa->info = (Helyiseg *)malloc(sizeof(Helyiseg)))) hiba(U_MEM);
						e_helyisega->leiras = e_helyiseg0->leiras;
						e_helyisega->idozito = 255;
						e_helyisega->sotet = e_helyiseg0->sotet;
						e_helyisega->lejar.szallapot = 0;
						e_helyisega->lejar.parameter = 0;
						e_helyisega->lejar.uzenet = 0;
						e_helyisega->belep.szallapot = 0;
						e_helyisega->belep.uzenet = 0;
						e_helyisega->kimegy.szallapot = 0;
						e_helyisega->kimegy.uzenet = 0;
						break;
					}
					case T_TARGY:
					{
						if (all == 1)
						{
							p->info = letrehoz(e_targy);
							pa = p->info;
						} else
						{
							pa = beszur(pa);
						}
						if (!(pa->info = (Targy *)malloc(sizeof(Targy)))) hiba(U_MEM);
						e_targya->leiras = e_targy0->leiras;
						e_targya->idozito = 255;
						e_targya->helyiseg = 255;
						e_targya->szereplonel = 255;
						e_targya->vizsgal.szallapot = 0;
						e_targya->vizsgal.uzenet = 0;
						e_targya->lejar.szallapot = 0;
						e_targya->lejar.parameter = 0;
						e_targya->lejar.uzenet = 0;
						e_targya->felvesz.szallapot = 0;
						e_targya->felvesz.uzenet = 0;
						e_targya->letesz.szallapot = 0;
						e_targya->letesz.uzenet = 0;
						e_targya->szakcio = 0;
						e_targya->szeszkoz = 0;
						e_targya->akcio = NULL;
						e_targya->eszkoz = NULL;
						break;
					}
					case T_AKADALY:
					{
						if (all == 1)
						{
							p->info = letrehoz(e_akadaly);
							pa = p->info;
						} else
						{
							pa = beszur(pa);
						}
						if (!(pa->info = (Akadaly *)malloc(sizeof(Akadaly)))) hiba(U_MEM);
						e_akadalya->leiras = e_akadaly0->leiras;
						e_akadalya->idozito = 255;
						e_akadalya->jarhato = e_akadaly0->jarhato;
						e_akadalya->vizsgal.szallapot = 0;
						e_akadalya->vizsgal.uzenet = 0;
						e_akadalya->lejar.szallapot = 0;
						e_akadalya->lejar.parameter = 0;
						e_akadalya->lejar.uzenet = 0;
						e_akadalya->szakcio = 0;
						e_akadalya->szeszkoz = 0;
						e_akadalya->akcio = NULL;
						e_akadalya->eszkoz = NULL;
						break;
					}
					case T_SZEREPLO:
					{
						if (all == 1)
						{
							p->info = letrehoz(e_szereplo);
							pa = p->info;
						} else
						{
							pa = beszur(pa);
						}
						if (!(pa->info = (Szereplo *)malloc(sizeof(Szereplo)))) hiba(U_MEM);
						e_szereploa->idozito = 255;
						e_szereploa->leiras = e_szereplo0->leiras;
						e_szereploa->helyiseg = 255;
						e_szereploa->irany = e_szereplo0->irany;
						e_szereploa->vizsgal.szallapot = 0;
						e_szereploa->vizsgal.uzenet = 0;
						e_szereploa->lejar.szallapot = 0;
						e_szereploa->lejar.parameter = 0;
						e_szereploa->lejar.uzenet = 0;
						e_szereploa->lep.szallapot = 0;
						e_szereploa->lep.parameter = 0;
						e_szereploa->lep.uzenet = 0;
						e_szereploa->iranyit.szallapot = 0;
						e_szereploa->iranyit.uzenet = 0;
						e_szereploa->szakcio = 0;
						e_szereploa->szeszkoz = 0;
						e_szereploa->szmeglat = 0;
						e_szereploa->szbeszel = 0;
						e_szereploa->szad = 0;
						e_szereploa->szmutat = 0;
						e_szereploa->akcio = NULL;
						e_szereploa->eszkoz = NULL;
						e_szereploa->meglat = NULL;
						e_szereploa->beszel = NULL;
						e_szereploa->ad = NULL;
						e_szereploa->mutat = NULL;
						break;
					}
				}
				continue;
			}
			i = 0;
			if ((strchr(s, '"')) || (!strchr(s, '=')))
				return fajlhiba(U_ROSSZSOR2, l);
			while ((s[i]) && (s[i] != '='))
			{
				t[i] = s[i];
				i++;
			}
			if (s[strlen(s)-1] == '=')
				return fajlhiba(U_KEVESPARAM, l);
			t[i] = 0;
			i++;
			szetszed(t, v, &x);
			*t = 0;
			cc = count(s, ',');
			switch (mit)
			{
				case T_HELYISEG:
				{
					if (!strcmp(v, S_LEJAR))
					{
						if (!all)
						{
							esemenypinit(&(e_helyiseg0->lejar), cc-1);
						}
						else
						{
							esemenypinit(&(e_helyisega->lejar), cc-1);
						}
					} else
					if (!strcmp(v, S_BE))
					{
						if (!all)
						{
							esemenyinit(&(e_helyiseg0->belep), cc);
						}
						else
						{
							esemenyinit(&(e_helyisega->belep), cc);
						}
					} else
					if (!strcmp(v, S_KI))
					{
						if (!all)
						{
							esemenyinit(&(e_helyiseg0->kimegy), cc);
						}
						else
						{
							esemenyinit(&(e_helyisega->kimegy), cc);
						}
					}
					break;
				}
				case T_TARGY:
				{
					if (!strcmp(v, S_VIZSGAL))
					{
						if (!all)
						{
							esemenyinit(&(e_targy0->vizsgal), cc);
						}
						else
						{
							esemenyinit(&(e_targya->vizsgal), cc);
						}
					} else
					if (!strcmp(v, S_LEJAR))
					{
						if (!all)
						{
							esemenypinit(&(e_targy0->lejar), cc-1);
						}
						else
						{
							esemenypinit(&(e_targya->lejar), cc-1);
						}
					} else
					if (!strcmp(v, S_FELVESZ))
					{
						if (!all)
						{
							esemenyinit(&(e_targy0->felvesz), cc);
						}
						else
						{
							esemenyinit(&(e_targya->felvesz), cc);
						}
					} else
					if (!strcmp(v, S_LETESZ))
					{
						if (!all)
						{
							esemenyinit(&(e_targy0->letesz), cc);
						}
						else
						{
							esemenyinit(&(e_targya->letesz), cc);
						}
					} else
					if (!strcmp(v, S_AKCIO))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_targy0->szakcio++;
							if (e_targy0->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_targy0->szakcio == 1)
							{
								e_targy0->akcio = letrehoz(e_targy0->akcio);
								pe1 = e_targy0->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
						else
						{
							e_targya->szakcio++;
							if (e_targya->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_targya->szakcio == 1)
							{
								e_targya->akcio = letrehoz(e_targya->akcio);
								pe1 = e_targya->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
					} else
					if (!strcmp(v, S_ESZKOZ))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_targy0->szeszkoz++;
							if (e_targy0->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_targy0->szeszkoz == 1)
							{
								e_targy0->eszkoz = letrehoz(e_targy0->eszkoz);
								pe2 = e_targy0->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
						else
						{
							e_targya->szeszkoz++;
							if (e_targya->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_targya->szeszkoz == 1)
							{
								e_targya->eszkoz = letrehoz(e_targya->eszkoz);
								pe2 = e_targya->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
					}
					break;
				}
				case T_AKADALY:
				{
					if (!strcmp(v, S_VIZSGAL))
					{
						if (!all)
						{
							esemenyinit(&(e_akadaly0->vizsgal), cc);
						}
						else
						{
							esemenyinit(&(e_akadalya->vizsgal), cc);
						}
					} else
					if (!strcmp(v, S_LEJAR))
					{
						if (!all)
						{
							esemenypinit(&(e_akadaly0->lejar), cc-1);
						}
						else
						{
							esemenypinit(&(e_akadalya->lejar), cc-1);
						}
					} else
					if (!strcmp(v, S_AKCIO))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_akadaly0->szakcio++;
							if (e_akadaly0->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_akadaly0->szakcio == 1)
							{
								e_akadaly0->akcio = letrehoz(e_akadaly0->akcio);
								pe1 = e_akadaly0->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
						else
						{
							e_akadalya->szakcio++;
							if (e_akadalya->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_akadalya->szakcio == 1)
							{
								e_akadalya->akcio = letrehoz(e_akadalya->akcio);
								pe1 = e_akadalya->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
					} else
					if (!strcmp(v, S_ESZKOZ))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_akadaly0->szeszkoz++;
							if (e_akadaly0->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_akadaly0->szeszkoz == 1)
							{
								e_akadaly0->eszkoz = letrehoz(e_akadaly0->eszkoz);
								pe2 = e_akadaly0->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
						else
						{
							e_akadalya->szeszkoz++;
							if (e_akadalya->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_akadalya->szeszkoz == 1)
							{
								e_akadalya->eszkoz = letrehoz(e_akadalya->eszkoz);
								pe2 = e_akadalya->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
					}
					break;
				}
				case T_SZEREPLO:
				{
					if (!strcmp(v, S_VIZSGAL))
					{
						if (!all)
						{
							esemenyinit(&(e_szereplo0->vizsgal), cc);
						}
						else
						{
							esemenyinit(&(e_szereploa->vizsgal), cc);
						}
					} else
					if (!strcmp(v, S_LEJAR))
					{
						if (!all)
						{
							esemenypinit(&(e_szereplo0->lejar), cc-1);
						}
						else
						{
							esemenypinit(&(e_szereploa->lejar), cc-1);
						}
					} else
					if (!strcmp(v, S_LEP))
					{
						if (!all)
						{
							esemenypinit(&(e_szereplo0->lep), cc-1);
						}
						else
						{
							esemenypinit(&(e_szereploa->lep), cc-1);
						}
					} else
					if (!strcmp(v, S_IRANYIT))
					{
						if (!all)
						{
							esemenyinit(&(e_szereplo0->iranyit), cc);
						}
						else
						{
							esemenyinit(&(e_szereploa->iranyit), cc);
						}
					} else
					if (!strcmp(v, S_AKCIO))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szakcio++;
							if (e_szereplo0->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szakcio == 1)
							{
								e_szereplo0->akcio = letrehoz(e_szereplo0->akcio);
								pe1 = e_szereplo0->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
						else
						{
							e_szereploa->szakcio++;
							if (e_szereploa->szakcio != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szakcio == 1)
							{
								e_szereploa->akcio = letrehoz(e_szereploa->akcio);
								pe1 = e_szereploa->akcio;
							}
							else
							{
								pe1 = beszur(pe1);
							}
							if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp1, cc-1);
						}
					} else
					if (!strcmp(v, S_ESZKOZ))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szeszkoz++;
							if (e_szereplo0->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szeszkoz == 1)
							{
								e_szereplo0->eszkoz = letrehoz(e_szereplo0->eszkoz);
								pe2 = e_szereplo0->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
						else
						{
							e_szereploa->szeszkoz++;
							if (e_szereploa->szeszkoz != x)
							{
								return sorszamhiba("\"eszkoz\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szeszkoz == 1)
							{
								e_szereploa->eszkoz = letrehoz(e_szereploa->eszkoz);
								pe2 = e_szereploa->eszkoz;
							}
							else
							{
								pe2 = beszur(pe2);
							}
							if (!(pe2->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp2, cc-1);
						}
					} else
					if (!strcmp(v, S_LAT))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szmeglat++;
							if (e_szereplo0->szmeglat != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szmeglat == 1)
							{
								e_szereplo0->meglat = letrehoz(e_szereplo0->meglat);
								pe3 = e_szereplo0->meglat;
							}
							else
							{
								pe3 = beszur(pe3);
							}
							if (!(pe3->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp3, cc-1);
						}
						else
						{
							e_szereploa->szmeglat++;
							if (e_szereploa->szmeglat != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szmeglat == 1)
							{
								e_szereploa->meglat = letrehoz(e_szereploa->meglat);
								pe3 = e_szereploa->meglat;
							}
							else
							{
								pe3 = beszur(pe3);
							}
							if (!(pe3->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp3, cc-1);
						}
					} else
					if (!strcmp(v, S_BESZEL))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szbeszel++;
							if (e_szereplo0->szbeszel != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szbeszel == 1)
							{
								e_szereplo0->beszel = letrehoz(e_szereplo0->beszel);
								pe4 = e_szereplo0->beszel;
							}
							else
							{
								pe4 = beszur(pe4);
							}
							if (!(pe4->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp4, cc-1);
						}
						else
						{
							e_szereploa->szbeszel++;
							if (e_szereploa->szbeszel != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szbeszel == 1)
							{
								e_szereploa->beszel = letrehoz(e_szereploa->beszel);
								pe4 = e_szereploa->beszel;
							}
							else
							{
								pe4 = beszur(pe4);
							}
							if (!(pe4->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp4, cc-1);
						}
					} else
					if (!strcmp(v, S_AD))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szad++;
							if (e_szereplo0->szad != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szad == 1)
							{
								e_szereplo0->ad = letrehoz(e_szereplo0->ad);
								pe5 = e_szereplo0->ad;
							}
							else
							{
								pe5 = beszur(pe5);
							}
							if (!(pe5->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp5, cc-1);
						}
						else
						{
							e_szereploa->szad++;
							if (e_szereploa->szad != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szad == 1)
							{
								e_szereploa->ad = letrehoz(e_szereploa->ad);
								pe5 = e_szereploa->ad;
							}
							else
							{
								pe5 = beszur(pe5);
							}
							if (!(pe5->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp5, cc-1);
						}
					} else
					if (!strcmp(v, S_MUTAT))
					{
						if (!cc) return fajlhiba(U_KEVESPARAM, l);
						if (!all)
						{
							e_szereplo0->szmutat++;
							if (e_szereplo0->szmutat != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereplo0->szmutat == 1)
							{
								e_szereplo0->mutat = letrehoz(e_szereplo0->mutat);
								pe6 = e_szereplo0->mutat;
							}
							else
							{
								pe6 = beszur(pe6);
							}
							if (!(pe6->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp6, cc-1);
						}
						else
						{
							e_szereploa->szmutat++;
							if (e_szereploa->szmutat != x)
							{
								return sorszamhiba("\"akcio\" esemÇnykezelãnek", x, l);
							}
							if (e_szereploa->szmutat == 1)
							{
								e_szereploa->mutat = letrehoz(e_szereploa->mutat);
								pe6 = e_szereploa->mutat;
							}
							else
							{
								pe6 = beszur(pe6);
							}
							if (!(pe6->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
							esemenypinit(e_esemenyp6, cc-1);
						}
					}
					break;
				}
			}
			he = 0;
			h = 0;
			while (1)
			{
				if ((s[i] == ',') || (!(s[i])))
				{
					t[h] = 0;
					e = atoi(t);
					switch (mit)
					{
						case T_INFO:
						{
							if (!strcmp(v, S_CIM))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (he > 1)
									return fajlhiba(U_SOKPARAM, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								cim = e;
							} else
							if (!strcmp(v, S_BEV))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (he > MAX_BEKEZDES)
									return fajlhiba(U_SOKPARAM, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								bevezeto[he] = e;
							} else
							if (!strcmp(v, S_EPI))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (he > MAX_BEKEZDES)
									return fajlhiba(U_SOKPARAM, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								epilogus[he] = e;
							} else
								return fajlhiba(U_ROSSZTUL, l);
							break;
						}
						case T_HELYISEG:
						{
							if (!strcmp(v, S_NEV))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_helyiseg0->nev = e;
								else
									return vhiba(S_NEV, l);
							} else
							if (!strcmp(v, S_LEIRAS))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_helyiseg0->leiras = e;
								else
								{
									e_helyisega->leiras = e;
								}
							} else
							if (!strcmp(v, S_IDO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_helyiseg0->idozito = e;
								else
									e_helyisega->idozito = e;
							} else
							if (!strcmp(v, S_KIJARAT))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > MAX_HELYISEG)
									return hhiba(S_H, l);
								if (he > 11)
									return fajlhiba(U_SOKPARAM, l);
								if (!all)
									e_helyiseg0->kijaratok[he] = (byte)e;
								else
									return vhiba(S_KIJARAT, l);
							} else
							if (!strcmp(v, S_SOTET))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_helyiseg0->sotet = e;
								else
								{
									e_helyisega->sotet = e;
								}
							} else
							if (!strcmp(v, S_LEJAR))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_helyiseg0->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_helyiseg0->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_helyiseg0->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_helyisega->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_helyisega->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_helyisega->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
							} else
							if (!strcmp(v, S_BE))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_helyiseg0->belep.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_helyiseg0->belep.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_helyisega->belep.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_helyisega->belep.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_KI))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_helyiseg0->kimegy.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_helyiseg0->kimegy.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_helyisega->kimegy.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_helyisega->kimegy.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
								return fajlhiba(U_ROSSZTUL, l);
							break;
						}
						case T_TARGY:
						{
							if (!strcmp(v, S_NEV))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_targy0->nev = e;
								else
									return vhiba(S_NEV, l);
							} else
							if (!strcmp(v, S_LEIRAS))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_targy0->leiras = e;
								else
								{
									e_targya->leiras = e;
								}
							} else
							if (!strcmp(v, S_IDO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_targy0->idozito = e;
								else
									e_targya->idozito = e;
							} else
							if (!strcmp(v, S_ELO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_targy0->elotag = e;
								else
									return vhiba(S_ELO, l);
							} else
							if (!strcmp(v, S_NEVELO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_targy0->nevelo = e;
								else
									return vhiba(S_NEVELO, l);
							} else
							if (!strcmp(v, S_HELY))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > MAX_HELYISEG)
									return hhiba(S_H, l);
								if (!all)
									e_targy0->helyiseg = e;
								else
									e_targya->helyiseg = e;
							} else
							if (!strcmp(v, S_SZER))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_targy0->szereplonel = e;
								else
									e_targya->szereplonel = e;
							} else
							if (!strcmp(v, S_ROGZ))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_targy0->rogzitett = e;
								else
									return vhiba(S_ROGZ, l);
							} else
							if (!strcmp(v, S_VIZSGAL))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targy0->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targy0->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targya->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targya->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_LEJAR))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_targy0->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_targy0->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_targy0->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_targya->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_targya->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_targya->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
							} else
							if (!strcmp(v, S_FELVESZ))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targy0->felvesz.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targy0->felvesz.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targya->felvesz.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targya->felvesz.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_LETESZ))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targy0->letesz.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targy0->letesz.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_targya->letesz.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_targya->letesz.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_AKCIO))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp1->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_ESZKOZ))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_TARGY)
											return hhiba(S_T, l);
										e_esemenyp2->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp2->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp2->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
								return fajlhiba(U_ROSSZTUL, l);
							break;
						}
						case T_AKADALY:
						{
							if (!strcmp(v, S_NEV))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_akadaly0->nev = e;
								else
									return vhiba(S_NEV, l);
							} else
							if (!strcmp(v, S_LEIRAS))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_akadaly0->leiras = e;
								else
								{
									e_akadalya->leiras = e;
								}
							} else
							if (!strcmp(v, S_IDO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_akadaly0->idozito = e;
								else
									e_akadalya->idozito = e;
							} else
							if (!strcmp(v, S_EGYIK))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > MAX_HELYISEG)
									return hhiba(S_H, l);
								if (!all)
									e_akadaly0->egyik = e;
								else
									return vhiba(S_EGYIK, l);
							} else
							if (!strcmp(v, S_MASIK))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > MAX_HELYISEG)
									return hhiba(S_H, l);
								if (!all)
									e_akadaly0->masik = e;
								else
									return vhiba(S_MASIK, l);
							} else
							if (!strcmp(v, S_JARHATO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_akadaly0->jarhato = e;
								else
									e_akadalya->jarhato = e;
							} else
							if (!strcmp(v, S_VIZSGAL))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_akadaly0->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_akadaly0->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_akadalya->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_akadalya->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_LEJAR))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_akadaly0->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_akadaly0->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_akadaly0->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_akadalya->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_akadalya->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_akadalya->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
							} else
							if (!strcmp(v, S_AKCIO))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp1->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_ESZKOZ))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_TARGY)
											return hhiba(S_T, l);
										e_esemenyp2->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp2->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp2->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
								return fajlhiba(U_ROSSZTUL, l);
							break;
						}
						case T_SZEREPLO:
						{
							if (!strcmp(v, S_NEV))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_szereplo0->nev = e;
								else
									return vhiba(S_NEV, l);
							} else
							if (!strcmp(v, S_LEIRAS))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_szereplo0->leiras = e;
								else
								{
									e_szereploa->leiras = e;
								}
							} else
							if (!strcmp(v, S_IDO))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_szereplo0->idozito = e;
								else
									e_szereploa->idozito = e;
							} else
							if (!strcmp(v, S_KOZ))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > szszoveg)
									return hhiba(S_SZ, l);
								if (!all)
									e_szereplo0->koznev = e;
								else
									return vhiba(S_KOZ, l);
							} else
							if (!strcmp(v, S_EGYEDI))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_szereplo0->egyedi = e;
								else
									return vhiba(S_EGYEDI, l);
							} else
							if (!strcmp(v, S_HELY))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > MAX_HELYISEG)
									return hhiba(S_H, l);
								if (!all)
									e_szereplo0->helyiseg = e;
								else
									e_szereploa->helyiseg = e;
							} else
							if (!strcmp(v, S_IRANY))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (e > 12)
									return hhiba("ir†ny", l);
								if (!all)
									e_szereplo0->irany = e;
								else
									e_szereploa->irany = e;
							} else
							if (!strcmp(v, S_IR))
							{
								if (!szam(t)) return fajlhiba(U_ROSSZP, l);
								if (!all)
									e_szereplo0->iranyithato = e;
								else
									return vhiba(S_IR, l);
								if (e) szjatekos++;
							} else
							if (!strcmp(v, S_VIZSGAL))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_szereplo0->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_szereplo0->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_szereploa->vizsgal.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_szereploa->vizsgal.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_LEJAR))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_szereplo0->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_szereplo0->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_szereplo0->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_szereploa->lejar.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_szereploa->lejar.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_szereploa->lejar.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
							} else
							if (!strcmp(v, S_LEP))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_szereplo0->lep.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_szereplo0->lep.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_szereplo0->lep.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										e_szereploa->lep.parameter = e;
									}
									else
									{
										if (he == 1)
										{
											if (!szam(t)) return fajlhiba(U_ROSSZP, l);
											if (e > szszoveg)
												return hhiba(S_SZ, l);
											e_szereploa->lep.uzenet = e;
										} else
										{
											if (ujallapot(t, &(e_szereploa->lep.allapot[he-2])))
												return fajlhiba(U_ROSSZALL, l);
										}
									}
								}
							} else
							if (!strcmp(v, S_IRANYIT))
							{
								if (!all)
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_szereplo0->iranyit.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_szereplo0->iranyit.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
								else
								{
									if (!he)
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_szereploa->iranyit.uzenet = e;
									}
									else
									{
										if (ujallapot(t, &(e_szereploa->iranyit.allapot[he-1])))
											return fajlhiba(U_ROSSZALL, l);
									}
								}
							} else
							if (!strcmp(v, S_AKCIO))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp1->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp1->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_ESZKOZ))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_TARGY)
											return hhiba(S_T, l);
										e_esemenyp2->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp2->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp2->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_LAT))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_SZEREPLO)
											return hhiba(S_T, l);
										e_esemenyp3->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp3->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp3->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_BESZEL))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp4->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp4->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp4->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_AD))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_TARGY)
											return hhiba(S_T, l);
										e_esemenyp5->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp5->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp5->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
							if (!strcmp(v, S_MUTAT))
							{
								switch (he)
								{
									case 0:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > MAX_TARGY)
											return hhiba(S_T, l);
										e_esemenyp6->parameter = e;
										break;
									}
									case 1:
									{
										if (!szam(t)) return fajlhiba(U_ROSSZP, l);
										if (e > szszoveg)
											return hhiba(S_SZ, l);
										e_esemenyp6->uzenet = e;
										break;
									}
									default:
									{
										if (ujallapot(t, &(e_esemenyp6->allapot[he-2])))
											return fajlhiba(U_ROSSZALL, l);
										break;
									}
								}
							} else
								return fajlhiba(U_ROSSZTUL, l);
							break;
						}
					}
					*t = 0;
					h = 0;
					he++;
					if (!(s[i])) break;
				}
				else
				{
					t[h] = s[i];
					h++;
				}
				i++;
			}
		}
	}
	switch (mit)
	{
		case T_HELYISEG:
		{
			if (!ssz) return nhiba(S_H);
			szhelyiseg = ssz;
			if (e_helyiseg0) e_helyiseg0->szallapot = all;
			break;
		}
		case T_TARGY:
		{
			if (!ssz) return nhiba(S_T);
			sztargy = ssz;
			e_targy0->szallapot = all;
			break;
		}
		case T_AKADALY:
		{
			if (!ssz) return nhiba(S_A);
			szakadaly = ssz;
			e_akadaly0->szallapot = all;
			break;
		}
		case T_SZEREPLO:
		{
			if (!ssz) return nhiba(S_S);
			szszereplo = ssz;
			e_szereplo0->szallapot = all;
			break;
		}
	}
	/* A leford°tott j†tÇk mentÇse */
	if (!(f2 = fopen(fn, "wb")))
	{
		writeln(U_MENTESH);
		return -1;
	}
	fputs(S_MK, f2);
	time(&fajlido);
	fwrite(&fajlido, sizeof(time_t), 1, f2);
	p = szoveg->kov;
	fwrite(&szszoveg, sizeof(szszoveg), 1, f2);
	for (i = 1; i <= szszoveg; i++)
	{
		fputs(p->info, f2);
		fputc(0, f2);
		p = p->kov;
	}
	fwrite(&cim, sizeof(cim), 1, f2);
	for (i = 0; i < MAX_BEKEZDES; i++)
	{
		fwrite(&bevezeto[i], 2, 1, f2);
	}
	for (i = 0; i < MAX_BEKEZDES; i++)
	{
		fwrite(&epilogus[i], 2, 1, f2);
	}
	fwrite(&szhelyiseg, sizeof(szhelyiseg), 1, f2);
	p = helyiseg;
	p0 = helyiseg0;
	ssz = 1;
	while (p0 && p0->info)
	{
		if ((!e_helyiseg0->leiras) && (!e_helyiseg0->nev))
		{
			fclose(f2);
			remove(fn);
			tulhiba("helyisÇgnek", "se le°r†sa, se neve", ssz);
		}
		fwrite(&(e_helyiseg0->szallapot), 1, 1, f2);
		fwrite(&(e_helyiseg0->idozito), 1, 1, f2);
		fwrite(&(e_helyiseg0->nev), 2, 1, f2);
		fwrite(&(e_helyiseg0->leiras), 2, 1, f2);
		fwrite(&(e_helyiseg0->sotet), 1, 1, f2);
		fwrite(e_helyiseg0->kijaratok, 12, 1, f2);
		for (i = 0; i < 12; i++)
		{
			if (e_helyiseg0->kijaratok[i] > szhelyiseg)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_H, e_helyiseg0->kijaratok[i]);
			}
		}
		e_helyiseg0->allapot = 0;
		e_helyiseg0->ido = e_helyiseg0->idozito;
		esemenypment(&(e_helyiseg0->lejar), f2);
		esemenyment(&(e_helyiseg0->belep), f2);
		esemenyment(&(e_helyiseg0->kimegy), f2);
		pa = e_helyiseg;
		while (pa && pa->info)
		{
			fwrite(&(e_helyisega->idozito), 1, 1, f2);
			fwrite(&(e_helyisega->leiras), 2, 1, f2);
			fwrite(&(e_helyisega->sotet), 1, 1, f2);
			esemenypment(&(e_helyisega->lejar), f2);
			esemenyment(&(e_helyisega->belep), f2);
			esemenyment(&(e_helyisega->kimegy), f2);
			pa = pa->kov;
		}
		ssz++;
		p0 = p0->kov;
		p = p->kov;
	}
	fwrite(&sztargy, sizeof(sztargy), 2, f2);
	ssz = 1;
	p = targy;
	p0 = targy0;
	while (p0 && p0->info)
	{
		if (!e_targy0->nev)
		{
			fclose(f2);
			remove(fn);
			tulhiba("t†rgynak", "neve", ssz);
		}
		fwrite(&(e_targy0->szallapot), 1, 1, f2);
		fwrite(&(e_targy0->idozito), 1, 1, f2);
		fwrite(&(e_targy0->nev), 2, 1, f2);
		fwrite(&(e_targy0->leiras), 2, 1, f2);
		fwrite(&(e_targy0->elotag), 2, 1, f2);
		fwrite(&(e_targy0->nevelo), 1, 1, f2);
		fwrite(&(e_targy0->helyiseg), 1, 1, f2);
		fwrite(&(e_targy0->szereplonel), 1, 1, f2);
		if (e_targy0->szereplonel)
		{
			if (e_targy0->helyiseg > szszereplo)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_S, e_targy0->helyiseg);
			}
		} else
		{
			if (e_targy0->helyiseg > szhelyiseg)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_H, e_targy0->helyiseg);
			}
		}
		fwrite(&(e_targy0->rogzitett), 1, 1, f2);
		e_targy0->allapot = 0;
		e_targy0->ido = e_targy0->idozito;
		e_targy0->hely = e_targy0->helyiseg;
		e_targy0->szer = e_targy0->szereplonel;
		esemenyment(&(e_targy0->vizsgal), f2);
		esemenypment(&(e_targy0->lejar), f2);
		esemenyment(&(e_targy0->felvesz), f2);
		esemenyment(&(e_targy0->letesz), f2);
		fwrite(&(e_targy0->szakcio), 1, 1, f2);
		pe1 = e_targy0->akcio;
		for (j = 0; j < e_targy0->szakcio; j++)
		{
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_targy0->szeszkoz), 1, 1, f2);
		pe1 = e_targy0->eszkoz;
		for (j = 0; j < e_targy0->szeszkoz; j++)
		{
			if (e_esemenyp1->parameter > sztargy)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_T, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		pa = e_targy;
		while (pa && pa->info)
		{
			fwrite(&(e_targya->idozito), 1, 1, f2);
			fwrite(&(e_targya->leiras), 2, 1, f2);
			fwrite(&(e_targya->helyiseg), 1, 1, f2);
			fwrite(&(e_targya->szereplonel), 1, 1, f2);
			if (e_targya->szereplonel != 255)
			{
				if (e_targya->szereplonel)
				{
					if (e_targya->helyiseg != 255)
					{
						if (e_targya->helyiseg > szszereplo)
						{
							fclose(f2);
							remove(fn);
							hivhiba(S_S, e_targya->helyiseg);
						}
					}
				} else
				{
					if (e_targya->helyiseg != 255)
					{
						if (e_targya->helyiseg > szhelyiseg)
						{
							fclose(f2);
							remove(fn);
							hivhiba(S_H, e_targya->helyiseg);
						}
					}
				}
			}
			esemenyment(&(e_targya->vizsgal), f2);
			esemenypment(&(e_targya->lejar), f2);
			esemenyment(&(e_targya->felvesz), f2);
			esemenyment(&(e_targya->letesz), f2);
			fwrite(&(e_targya->szakcio), 1, 1, f2);
			pe1 = e_targya->akcio;
			for (j = 0; j < e_targya->szakcio; j++)
			{
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_targya->szeszkoz), 1, 1, f2);
			pe1 = e_targya->eszkoz;
			for (j = 0; j < e_targya->szeszkoz; j++)
			{
				if (e_esemenyp1->parameter > sztargy)
				{
					fclose(f2);
					remove(fn);
					hivhiba(S_T, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			pa = pa->kov;
		}
    ssz++;
		p0 = p0->kov;
		p = p->kov;
	}
	fwrite(&szakadaly, sizeof(szakadaly), 1, f2);
	ssz = 1;
	p = akadaly;
	p0 = akadaly0;
	while (p0 && p0->info)
	{
		if (!e_akadaly0->nev)
		{
			fclose(f2);
			remove(fn);
			tulhiba("akad†lynak", "neve", ssz);
		}
		fwrite(&(e_akadaly0->szallapot), 1, 1, f2);
		fwrite(&(e_akadaly0->idozito), 1, 1, f2);
		fwrite(&(e_akadaly0->nev), 2, 1, f2);
		fwrite(&(e_akadaly0->leiras), 2, 1, f2);
		if (e_akadaly0->egyik > szhelyiseg)
		{
			fclose(f2);
			remove(fn);
			hivhiba(S_H, e_akadaly0->egyik);
		}
		if (e_akadaly0->masik > szhelyiseg)
		{
			fclose(f2);
			remove(fn);
			hivhiba(S_H, e_akadaly0->masik);
		}
		fwrite(&(e_akadaly0->egyik), 1, 1, f2);
		fwrite(&(e_akadaly0->masik), 1, 1, f2);
		fwrite(&(e_akadaly0->jarhato), 1, 1, f2);
		e_akadaly0->allapot = 0;
		e_akadaly0->ido = e_akadaly0->idozito;
		esemenyment(&(e_akadaly0->vizsgal), f2);
		esemenypment(&(e_akadaly0->lejar), f2);
		fwrite(&(e_akadaly0->szakcio), 1, 1, f2);
		pe1 = e_akadaly0->akcio;
		for (j = 0; j < e_akadaly0->szakcio; j++)
		{
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_akadaly0->szeszkoz), 1, 1, f2);
		pe1 = e_akadaly0->eszkoz;
		for (j = 0; j < e_akadaly0->szeszkoz; j++)
		{
			if (e_esemenyp1->parameter > sztargy)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_T, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		pa = e_akadaly;
		while (pa && pa->info)
		{
			fwrite(&(e_akadalya->idozito), 1, 1, f2);
			fwrite(&(e_akadalya->leiras), 2, 1, f2);
			fwrite(&(e_akadalya->jarhato), 1, 1, f2);
			esemenyment(&(e_akadalya->vizsgal), f2);
			esemenypment(&(e_akadalya->lejar), f2);
			fwrite(&(e_akadalya->szakcio), 1, 1, f2);
			pe1 = e_akadalya->akcio;
			for (j = 0; j < e_akadalya->szakcio; j++)
			{
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_akadalya->szeszkoz), 1, 1, f2);
			pe1 = e_akadalya->eszkoz;
			for (j = 0; j < e_akadalya->szeszkoz; j++)
			{
				if (e_esemenyp1->parameter > sztargy)
				{
					fclose(f2);
					remove(fn);
					hivhiba(S_T, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			pa = pa->kov;
		}
		p0 = p0->kov;
		p = p->kov;
	}
	fwrite(&szszereplo, sizeof(szszereplo), 1, f2);
	p = szereplo;
	p0 = szereplo0;
	ssz = 1;
	while (p0 && p0->info)
	{
		fwrite(&(e_szereplo0->szallapot), 1, 1, f2);
		fwrite(&(e_szereplo0->idozito), 1, 1, f2);
		fwrite(&(e_szereplo0->nev), 2, 1, f2);
		fwrite(&(e_szereplo0->leiras), 2, 1, f2);
		fwrite(&(e_szereplo0->koznev), 2, 1, f2);
		fwrite(&(e_szereplo0->egyedi), 1, 1, f2);
		fwrite(&(e_szereplo0->helyiseg), 1, 1, f2);
		e_szereplo0->allapot = 0;
		e_szereplo0->ido = e_szereplo0->idozito;
		e_szereplo0->hely = e_szereplo0->helyiseg;
		if (e_szereplo0->helyiseg > szhelyiseg)
		{
			fclose(f2);
			remove(fn);
			hivhiba(S_H, e_szereplo0->helyiseg);
		}
		fwrite(&(e_szereplo0->irany), 1, 1, f2);
		fwrite(&(e_szereplo0->iranyithato), 1, 1, f2);
		if ((!jatekos) && (e_szereplo0->iranyithato))
			jatekos = ssz;
		if (e_szereplo0->iranyithato)
		{
			if (!e_szereplo0->nev)
			{
				fclose(f2);
				remove(fn);
				tulhiba("szereplãnek", "neve", ssz);
			}
			if ((!e_szereplo0->helyiseg) && (szjatekos == 1))
			{
				fclose(f2);
				remove(fn);
				tulhiba(S_S, "sehol", ssz);
			}
		} else
		{
			if ((!(e_szereplo0->nev)) & (!(e_szereplo0->koznev)))
			{
				fclose(f2);
				remove(fn);
				tulhiba("szereplãnek", "neve", ssz);
			}
		}
		esemenyment(&(e_szereplo0->vizsgal), f2);
		esemenypment(&(e_szereplo0->lejar), f2);
		esemenypment(&(e_szereplo0->lep), f2);
		esemenyment(&(e_szereplo0->iranyit), f2);
		fwrite(&(e_szereplo0->szakcio), 1, 1, f2);
		pe1 = e_szereplo0->akcio;
		for (j = 0; j < e_szereplo0->szakcio; j++)
		{
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_szereplo0->szeszkoz), 1, 1, f2);
		pe1 = e_szereplo0->eszkoz;
		for (j = 0; j < e_szereplo0->szeszkoz; j++)
		{
			if (e_esemenyp1->parameter > sztargy)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_T, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_szereplo0->szmeglat), 1, 1, f2);
		pe1 = e_szereplo0->meglat;
		for (j = 0; j < e_szereplo0->szmeglat; j++)
		{
			if (e_esemenyp1->parameter > szszereplo)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_S, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_szereplo0->szbeszel), 1, 1, f2);
		pe1 = e_szereplo0->beszel;
		for (j = 0; j < e_szereplo0->szbeszel; j++)
		{
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_szereplo0->szad), 1, 1, f2);
		pe1 = e_szereplo0->ad;
		for (j = 0; j < e_szereplo0->szad; j++)
		{
			if (e_esemenyp1->parameter > sztargy)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_T, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		fwrite(&(e_szereplo0->szmutat), 1, 1, f2);
		pe1 = e_szereplo0->mutat;
		for (j = 0; j < e_szereplo0->szmutat; j++)
		{
			if (e_esemenyp1->parameter > sztargy)
			{
				fclose(f2);
				remove(fn);
				hivhiba(S_T, e_esemenyp1->parameter);
			}
			esemenypment(e_esemenyp1, f2);
			pe1 = pe1->kov;
		}
		pa = e_szereplo;
		while (pa && pa->info)
		{
			if ((szjatekos == 1) && (e_szereplo0->iranyithato) && (!(e_szereploa->helyiseg)))
			{
				fclose(f2);
				remove(fn);
				hiba("Ha csak egy ir†ny°that¢ szereplã van, nem lehet eltÅntetni azt az egyet!");
			}
			fwrite(&(e_szereploa->idozito), 1, 1, f2);
			fwrite(&(e_szereploa->leiras), 2, 1, f2);
			fwrite(&(e_szereploa->helyiseg), 1, 1, f2);
			fwrite(&(e_szereploa->irany), 1, 1, f2);
			esemenyment(&(e_szereploa->vizsgal), f2);
			esemenypment(&(e_szereploa->lejar), f2);
			esemenypment(&(e_szereploa->lep), f2);
			esemenyment(&(e_szereploa->iranyit), f2);
			fwrite(&(e_szereploa->szakcio), 1, 1, f2);
			pe1 = e_szereploa->akcio;
			for (j = 0; j < e_szereploa->szakcio; j++)
			{
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_szereploa->szeszkoz), 1, 1, f2);
			pe1 = e_szereploa->eszkoz;
			for (j = 0; j < e_szereploa->szeszkoz; j++)
			{
				if (e_esemenyp1->parameter > sztargy)
				{
					fclose(f2);
					remove(fn);
					hivhiba(S_T, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_szereploa->szmeglat), 1, 1, f2);
			pe1 = e_szereploa->meglat;
			for (j = 0; j < e_szereploa->szmeglat; j++)
			{
				if (e_esemenyp1->parameter > szszereplo)
				{
					fclose(f2);
					remove(fn);
					hivhiba(S_S, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_szereploa->szbeszel), 1, 1, f2);
			pe1 = e_szereploa->beszel;
			for (j = 0; j < e_szereploa->szbeszel; j++)
			{
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_szereploa->szad), 1, 1, f2);
			pe1 = e_szereploa->ad;
			for (j = 0; j < e_szereploa->szad; j++)
			{
				if (e_esemenyp1->parameter > sztargy)
				{
					fclose(f2);
				remove(fn);
					hivhiba(S_T, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			fwrite(&(e_szereploa->szmutat), 1, 1, f2);
			pe1 = e_szereploa->mutat;
			for (j = 0; j < e_szereploa->szmutat; j++)
			{
				if (e_esemenyp1->parameter > sztargy)
				{
					fclose(f2);
					remove(fn);
					hivhiba(S_T, e_esemenyp1->parameter);
				}
				esemenypment(e_esemenyp1, f2);
				pe1 = pe1->kov;
			}
			pa = pa->kov;
		}
		ssz++;
		p0 = p0->kov;
		p = p->kov;
	}
	if (!szjatekos)
	{
		fclose(f2);
		remove(fn);
		hiba(U_NINCSJ);
	}
	if (fclose(f2) == EOF)
	{
		hiba(U_MENTESH);
		return -1;
	}
	free(s);
	free(t);
	free(v);
	return 0;
}

/* Betîlt egy leford°tott kalandj†tÇk-f†jlt. */
int jatekot(FILE *f)
{
	word i, j, l;
	Lista *p, *p0, *pa, *pe1;
	*seged = 0;
	fread(&fajlido, sizeof(time_t), 1, f);
	p = szoveg;
	fread(&szszoveg, sizeof(szszoveg), 1, f);
	for (i = 0; i < szszoveg; i++)
	{
		l = 0;
		while (1)
		{
			if (!(seged[l] = fgetc(f))) break;
			l++;
		}
		p = beszur(p);
		if (!(p->info = (char *)malloc(l+1))) hiba(U_MEM);
		strcpy(p->info, seged);
		*seged = 0;
	}
	fread(&cim, sizeof(cim), 1, f);
	for (i = 0; i < MAX_BEKEZDES; i++)
	{
		fread(&bevezeto[i], 2, 1, f);
	}
	for (i = 0; i < MAX_BEKEZDES; i++)
	{
		fread(&epilogus[i], 2, 1, f);
	}
	fread(&szhelyiseg, sizeof(szhelyiseg), 1, f);
	p0 = helyiseg0;
	p = helyiseg;
	for (i = 0; i < szhelyiseg; i++)
	{
		if (i)
		{
			p0 = beszur(p0);
			p = beszur(p);
		}
		if (!(p0->info = (Helyiseg0 *)malloc(sizeof(Helyiseg0)))) hiba(U_MEM);
		fread(&(e_helyiseg0->szallapot), 1, 1, f);
		fread(&(e_helyiseg0->idozito), 1, 1, f);
		e_helyiseg0->allapot = 0;
		e_helyiseg0->ido = e_helyiseg0->idozito;
		fread(&(e_helyiseg0->nev), 2, 1, f);
		fread(&(e_helyiseg0->leiras), 2, 1, f);
		fread(&(e_helyiseg0->sotet), 1, 1, f);
		fread(e_helyiseg0->kijaratok, 12, 1, f);
		esemenyptolt(&(e_helyiseg0->lejar), f);
		esemenytolt(&(e_helyiseg0->belep), f);
		esemenytolt(&(e_helyiseg0->kimegy), f);
		if (e_helyiseg0->szallapot)
		{
			p->info = letrehoz(e_helyiseg);
			pa = p->info;
			for (j = 0; j < e_helyiseg0->szallapot; j++)
			{
				if (j)
				{
					pa = beszur(pa);
				}
				if (!(pa->info = (Helyiseg *)malloc(sizeof(Helyiseg)))) hiba(U_MEM);
				fread(&(e_helyisega->idozito), 1, 1, f);
				fread(&(e_helyisega->leiras), 2, 1, f);
				fread(&(e_helyisega->sotet), 1, 1, f);
				esemenyptolt(&(e_helyisega->lejar), f);
				esemenytolt(&(e_helyisega->belep), f);
				esemenytolt(&(e_helyisega->kimegy), f);
			}
		}
	}
	fread(&sztargy, sizeof(sztargy), 2, f);
	p0 = targy0;
	p = targy;
	for (i = 0; i < sztargy; i++)
	{
		if (i)
		{
			p0 = beszur(p0);
			p = beszur(p);
		}
		if (!(p0->info = (Targy0 *)malloc(sizeof(Targy0)))) hiba(U_MEM);
		fread(&(e_targy0->szallapot), 1, 1, f);
		fread(&(e_targy0->idozito), 1, 1, f);
		fread(&(e_targy0->nev), 2, 1, f);
		fread(&(e_targy0->leiras), 2, 1, f);
		fread(&(e_targy0->elotag), 2, 1, f);
		fread(&(e_targy0->nevelo), 1, 1, f);
		fread(&(e_targy0->helyiseg), 1, 1, f);
		fread(&(e_targy0->szereplonel), 1, 1, f);
		fread(&(e_targy0->rogzitett), 1, 1, f);
		e_targy0->allapot = 0;
		e_targy0->ido = e_targy0->idozito;
		e_targy0->hely = e_targy0->helyiseg;
		e_targy0->szer = e_targy0->szereplonel;
		esemenytolt(&(e_targy0->vizsgal), f);
		esemenyptolt(&(e_targy0->lejar), f);
		esemenytolt(&(e_targy0->felvesz), f);
		esemenytolt(&(e_targy0->letesz), f);
		e_targy0->akcio = NULL;
		fread(&(e_targy0->szakcio), 1, 1, f);
		if (e_targy0->szakcio)
		{
			e_targy0->akcio = letrehoz(e_targy0->akcio);
			pe1 = e_targy0->akcio;
			for (j = 0; j < e_targy0->szakcio; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_targy0->eszkoz = NULL;
		fread(&(e_targy0->szeszkoz), 1, 1, f);
		if (e_targy0->szeszkoz)
		{
			e_targy0->eszkoz = letrehoz(e_targy0->eszkoz);
			pe1 = e_targy0->eszkoz;
			for (j = 0; j < e_targy0->szeszkoz; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		if (e_targy0->szallapot)
		{
			p->info = letrehoz(e_targy);
			pa = p->info;
			for (j = 0; j < e_targy0->szallapot; j++)
			{
				if (j)
				{
					pa = beszur(pa);
				}
				if (!(pa->info = (Targy *)malloc(sizeof(Targy)))) hiba(U_MEM);
				fread(&(e_targya->idozito), 1, 1, f);
				fread(&(e_targya->leiras), 2, 1, f);
				fread(&(e_targya->helyiseg), 1, 1, f);
				fread(&(e_targya->szereplonel), 1, 1, f);
				esemenytolt(&(e_targya->vizsgal), f);
				esemenyptolt(&(e_targya->lejar), f);
				esemenytolt(&(e_targya->felvesz), f);
				esemenytolt(&(e_targya->letesz), f);
				e_targya->akcio = NULL;
				fread(&(e_targya->szakcio), 1, 1, f);
				if (e_targya->szakcio)
				{
					e_targya->akcio = letrehoz(e_targya->akcio);
					pe1 = e_targya->akcio;
					for (l = 0; l < e_targya->szakcio; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_targya->eszkoz = NULL;
				fread(&(e_targya->szeszkoz), 1, 1, f);
				if (e_targya->szeszkoz)
				{
					e_targya->eszkoz = letrehoz(e_targya->eszkoz);
					pe1 = e_targya->eszkoz;
					for (l = 0; l < e_targya->szeszkoz; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
			}
		}
	}
	fread(&szakadaly, sizeof(szakadaly), 1, f);
	p0 = akadaly0;
	p = akadaly;
	for (i = 0; i < szakadaly; i++)
	{
		if (i)
		{
			p0 = beszur(p0);
			p = beszur(p);
		}
		if (!(p0->info = (Akadaly0 *)malloc(sizeof(Akadaly0)))) hiba(U_MEM);
		fread(&(e_akadaly0->szallapot), 1, 1, f);
		fread(&(e_akadaly0->idozito), 1, 1, f);
		fread(&(e_akadaly0->nev), 2, 1, f);
		fread(&(e_akadaly0->leiras), 2, 1, f);
		fread(&(e_akadaly0->egyik), 1, 1, f);
		fread(&(e_akadaly0->masik), 1, 1, f);
		fread(&(e_akadaly0->jarhato), 1, 1, f);
		e_akadaly0->allapot = 0;
		e_akadaly0->ido = e_akadaly0->idozito;
		esemenytolt(&(e_akadaly0->vizsgal), f);
		esemenyptolt(&(e_akadaly0->lejar), f);
		e_akadaly0->akcio = NULL;
		fread(&(e_akadaly0->szakcio), 1, 1, f);
		if (e_akadaly0->szakcio)
		{
			e_akadaly0->akcio = letrehoz(e_akadaly0->akcio);
			pe1 = e_akadaly0->akcio;
			for (j = 0; j < e_akadaly0->szakcio; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_akadaly0->eszkoz = NULL;
		fread(&(e_akadaly0->szeszkoz), 1, 1, f);
		if (e_akadaly0->szeszkoz)
		{
			e_akadaly0->eszkoz = letrehoz(e_akadaly0->eszkoz);
			pe1 = e_akadaly0->eszkoz;
			for (j = 0; j < e_akadaly0->szeszkoz; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		if (e_akadaly0->szallapot)
		{
			p->info = letrehoz(e_akadaly);
			pa = p->info;
			for (j = 0; j < e_akadaly0->szallapot; j++)
			{
				if (j)
				{
					pa = beszur(pa);
				}
				if (!(pa->info = (Akadaly *)malloc(sizeof(Akadaly)))) hiba(U_MEM);
				fread(&(e_akadalya->idozito), 1, 1, f);
				fread(&(e_akadalya->leiras), 2, 1, f);
				fread(&(e_akadalya->jarhato), 1, 1, f);
				esemenytolt(&(e_akadalya->vizsgal), f);
				esemenyptolt(&(e_akadalya->lejar), f);
				e_akadalya->akcio = NULL;
				fread(&(e_akadalya->szakcio), 1, 1, f);
				if (e_akadalya->szakcio)
				{
					e_akadalya->akcio = letrehoz(e_akadalya->akcio);
					pe1 = e_akadalya->akcio;
					for (l = 0; l < e_akadalya->szakcio; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_akadalya->eszkoz = NULL;
				fread(&(e_akadalya->szeszkoz), 1, 1, f);
				if (e_akadalya->szeszkoz)
				{
					e_akadalya->eszkoz = letrehoz(e_akadalya->eszkoz);
					pe1 = e_akadalya->eszkoz;
					for (l = 0; l < e_akadalya->szeszkoz; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
			}
		}
	}
	fread(&szszereplo, sizeof(szszereplo), 1, f);
	p0 = szereplo0;
	p = szereplo;
	for (i = 0; i < szszereplo; i++)
	{
		if (i)
		{
			p0 = beszur(p0);
			p = beszur(p);
		}
		if (!(p0->info = (Szereplo0 *)malloc(sizeof(Szereplo0)))) hiba(U_MEM);
		fread(&(e_szereplo0->szallapot), 1, 1, f);
		fread(&(e_szereplo0->idozito), 1, 1, f);
		fread(&(e_szereplo0->nev), 2, 1, f);
		fread(&(e_szereplo0->leiras), 2, 1, f);
		fread(&(e_szereplo0->koznev), 2, 1, f);
		fread(&(e_szereplo0->egyedi), 1, 1, f);
		fread(&(e_szereplo0->helyiseg), 1, 1, f);
		fread(&(e_szereplo0->irany), 1, 1, f);
		fread(&(e_szereplo0->iranyithato), 1, 1, f);
		if (e_szereplo0->iranyithato) szjatekos++;
		if ((!jatekos) && (e_szereplo0->iranyithato))
			jatekos = i+1;
		e_szereplo0->allapot = 0;
		e_szereplo0->ido = e_szereplo0->idozito;
		e_szereplo0->hely = e_szereplo0->helyiseg;
		esemenytolt(&(e_szereplo0->vizsgal), f);
		esemenyptolt(&(e_szereplo0->lejar), f);
		esemenyptolt(&(e_szereplo0->lep), f);
		esemenytolt(&(e_szereplo0->iranyit), f);
		e_szereplo0->akcio = NULL;
		fread(&(e_szereplo0->szakcio), 1, 1, f);
		if (e_szereplo0->szakcio)
		{
			e_szereplo0->akcio = letrehoz(e_szereplo0->akcio);
			pe1 = e_szereplo0->akcio;
			for (j = 0; j < e_szereplo0->szakcio; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_szereplo0->eszkoz = NULL;
		fread(&(e_szereplo0->szeszkoz), 1, 1, f);
		if (e_szereplo0->szeszkoz)
		{
			e_szereplo0->eszkoz = letrehoz(e_szereplo0->eszkoz);
			pe1 = e_szereplo0->eszkoz;
			for (j = 0; j < e_szereplo0->szeszkoz; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_szereplo0->meglat = NULL;
		fread(&(e_szereplo0->szmeglat), 1, 1, f);
		if (e_szereplo0->szmeglat)
		{
			e_szereplo0->meglat = letrehoz(e_szereplo0->meglat);
			pe1 = e_szereplo0->meglat;
			for (j = 0; j < e_szereplo0->szmeglat; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_szereplo0->beszel = NULL;
		fread(&(e_szereplo0->szbeszel), 1, 1, f);
		if (e_szereplo0->szbeszel)
		{
			e_szereplo0->beszel = letrehoz(e_szereplo0->beszel);
			pe1 = e_szereplo0->beszel;
			for (j = 0; j < e_szereplo0->szbeszel; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_szereplo0->ad = NULL;
		fread(&(e_szereplo0->szad), 1, 1, f);
		if (e_szereplo0->szad)
		{
			e_szereplo0->ad = letrehoz(e_szereplo0->ad);
			pe1 = e_szereplo0->ad;
			for (j = 0; j < e_szereplo0->szad; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		e_szereplo0->mutat = NULL;
		fread(&(e_szereplo0->szmutat), 1, 1, f);
		if (e_szereplo0->szmutat)
		{
			e_szereplo0->mutat = letrehoz(e_szereplo0->mutat);
			pe1 = e_szereplo0->mutat;
			for (j = 0; j < e_szereplo0->szmutat; j++)
			{
				if (j)
				{
					pe1 = beszur(pe1);
				}
				if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
				esemenyptolt(e_esemenyp1, f);
			}
		}
		if (e_szereplo0->szallapot)
		{
			p->info = letrehoz(e_szereplo);
			pa = p->info;
			for (j = 0; j < e_szereplo0->szallapot; j++)
			{
				if (j)
				{
					pa = beszur(pa);
				}
				if (!(pa->info = (Szereplo *)malloc(sizeof(Szereplo)))) hiba(U_MEM);
				fread(&(e_szereploa->idozito), 1, 1, f);
				fread(&(e_szereploa->leiras), 2, 1, f);
				fread(&(e_szereploa->helyiseg), 1, 1, f);
				fread(&(e_szereploa->irany), 1, 1, f);
				esemenytolt(&(e_szereploa->vizsgal), f);
				esemenyptolt(&(e_szereploa->lejar), f);
				esemenyptolt(&(e_szereploa->lep), f);
				esemenytolt(&(e_szereploa->iranyit), f);
				e_szereploa->akcio = NULL;
				fread(&(e_szereploa->szakcio), 1, 1, f);
				if (e_szereploa->szakcio)
				{
					e_szereploa->akcio = letrehoz(e_szereploa->akcio);
					pe1 = e_szereploa->akcio;
					for (l = 0; l < e_szereploa->szakcio; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_szereploa->eszkoz = NULL;
				fread(&(e_szereploa->szeszkoz), 1, 1, f);
				if (e_szereploa->szeszkoz)
				{
					e_szereploa->eszkoz = letrehoz(e_szereploa->eszkoz);
					pe1 = e_szereploa->eszkoz;
					for (l = 0; l < e_szereploa->szeszkoz; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_szereploa->meglat = NULL;
				fread(&(e_szereploa->szmeglat), 1, 1, f);
				if (e_szereploa->szmeglat)
				{
					e_szereploa->meglat = letrehoz(e_szereploa->meglat);
					pe1 = e_szereploa->meglat;
					for (l = 0; l < e_szereploa->szmeglat; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_szereploa->beszel = NULL;
				fread(&(e_szereploa->szbeszel), 1, 1, f);
				if (e_szereploa->szbeszel)
				{
					e_szereploa->beszel = letrehoz(e_szereploa->beszel);
					pe1 = e_szereploa->beszel;
					for (l = 0; l < e_szereploa->szbeszel; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_szereploa->ad = NULL;
				fread(&(e_szereploa->szad), 1, 1, f);
				if (e_szereploa->szad)
				{
					e_szereploa->ad = letrehoz(e_szereploa->ad);
					pe1 = e_szereploa->ad;
					for (l = 0; l < e_szereploa->szad; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
				e_szereploa->mutat = NULL;
				fread(&(e_szereploa->szmutat), 1, 1, f);
				if (e_szereploa->szmutat)
				{
					e_szereploa->mutat = letrehoz(e_szereploa->mutat);
					pe1 = e_szereploa->mutat;
					for (l = 0; l < e_szereploa->szmutat; l++)
					{
						if (l)
						{
							pe1 = beszur(pe1);
						}
						if (!(pe1->info = (EsemenyP *)malloc(sizeof(EsemenyP)))) hiba(U_MEM);
						esemenyptolt(e_esemenyp1, f);
					}
				}
			}
		}
	}
	return 0;
}

/* Betîlt egy elmentett j†tÇk†llapotot. */
int mentest(FILE *f)
{
	Lista *p0;
	word i;
	byte a;
	time_t fi;
	fread(&fi, sizeof(fi), 1, f);
	if (fi != fajlido) return -1;
	jatekos = 0;
	p0 = helyiseg0;
	for (i = 0; i < szhelyiseg; i++)
	{
		fread(&a, 1, 1, f);
		ujha(i+1, a);
		fread(&(e_helyiseg0->ido), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = targy0;
	for (i = 0; i < sztargy; i++)
	{
		fread(&a, 1, 1, f);
		ujta(i+1, a);
		fread(&(e_targy0->ido), 1, 1, f);
		fread(&(e_targy0->hely), 1, 1, f);
		fread(&(e_targy0->szer), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = akadaly0;
	for (i = 0; i < szakadaly; i++)
	{
		fread(&a, 1, 1, f);
		ujaa(i+1, a);
		fread(&(e_akadaly0->ido), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		fread(&a, 1, 1, f);
		ujsa(i+1, a);
		fread(&(e_szereplo0->ido), 1, 1, f);
		fread(&(e_szereplo0->hely), 1, 1, f);
		p0 = p0->kov;
	}
	fread(&jatekos, 1, 1, f);
	return 0;
}

/* Betîlt egy megadott nev˚ forr†s- vagy kalandj†tÇk-f†jlt.
Ha olvas†si hiba lÇpett fel, -1-et ad vissza, ha a f†jl hib†s szerkezet˚, -2-ãt,
ha a f†jl nem forr†sf†jl vagy kalandj†tÇk-f†jl, -3-at, siker esetÇn 0-t. */
int betoltfk(char *s)
{
	FILE *f;
	if (!(f = fopen(s, "rt")))
		return -1;
	/* A f†jl t°pus†nak meg†llap°t†sa */
	fgets(seged, 512, f);
	seged[4] = 0;
	if (!strcmp(seged, S_MF))
	{
		forras = 1;
		write(s);
		writeln(" feldolgoz†sa...");
		if (strrchr(s, '.') >= strrchr(s, '\\'))
			s[strrchr(s, '.')-s] = 0;
		strcat(s, ".mkf");
		if (forrast(f, s))
		{
			fclose(f);
			remove(s);
			return -2;
		}
	}
	else
	{
		if (!strcmp(seged, S_MK))
		{
			fclose(f);
			if (!(f = fopen(s, "rb")))
				return -1;
			fseek(f, 4, 0);
			write(s);
			writeln(U_TOLTES);
			if (jatekot(f))
			{
				fclose(f);
				return -2;
			}
		}
		else
		{
			fclose(f);
			return -3;
		}
	}
	fclose(f);
	strcpy(jatekfn, s);
	return 0;
}

/* Betîlt egy elmentett j†tÇk†llapotot. VisszatÇrÇsi ÇrtÇke ugyanaz, mint az elãzã fÅggvÇnynek, */
int betoltm(char *s)
{
	FILE *f;
	char h[5];
	if (strrchr(s, '.') <= strrchr(s, '\\')) strcat(s, ".mmf");
	if (!(f = fopen(s, "rb")))
	{
		return -1;
	}
	fread(h, sizeof(char), 4, f);
	h[4] = 0;
	if (!strcmp(h, S_MM))
	{
		write(s);
		writeln(U_TOLTES);
		fseek(f, 4, 0);
		if (mentest(f))
		{
			fclose(f);
			return -2;
		}
	}
	else
	{
		fclose(f);
		return -3;
	}
	return 0;
}

/* Elmenti a j†tÇk aktu†lis †llapot†t egy megadott nev˚ f†jlba. */
int elment(char *s)
{
	FILE *f;
	word i;
	Lista *p0;
	if (strrchr(s, '.') <= strrchr(s, '\\')) strcat(s, ".mmf");
	write(s);
	writeln(" mentÇse...");
	if (!(f = fopen(s, "wb")))
		return -1;
	fputs(S_MM, f);
	fwrite(&fajlido, sizeof(time_t), 1, f);
	p0 = helyiseg0;
	for (i = 0; i < szhelyiseg; i++)
	{
		fwrite(&(e_helyiseg0->allapot), 1, 1, f);
		fwrite(&(e_helyiseg0->ido), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = targy0;
	for (i = 0; i < sztargy; i++)
	{
		fwrite(&(e_targy0->allapot), 1, 1, f);
		fwrite(&(e_targy0->ido), 1, 1, f);
		fwrite(&(e_targy0->hely), 1, 1, f);
		fwrite(&(e_targy0->szer), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = akadaly0;
	for (i = 0; i < szakadaly; i++)
	{
		fwrite(&(e_akadaly0->allapot), 1, 1, f);
		fwrite(&(e_akadaly0->ido), 1, 1, f);
		p0 = p0->kov;
	}
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		fwrite(&(e_szereplo0->allapot), 1, 1, f);
		fwrite(&(e_szereplo0->ido), 1, 1, f);
		fwrite(&(e_szereplo0->hely), 1, 1, f);
		p0 = p0->kov;
	}
	fwrite(&jatekos, 1, 1, f);
	fclose(f);
	strcpy(mentesfn, s);
	return 0;
}

/* Betîlti a be†ll°t†sokat a maszk.mbf f†jlb¢l. */
int betoltb(void)
{
	FILE *f;
	if (!(f = fopen(S_MBFN, "rt"))) return -1;
	if (!(fgets(segeda, 5, f))) return -1;
	segeda[5] = 0;
	if (strcmp(segeda, S_MB)) return -1;
	while (!feof(f))
	{
		if (fgets(segeda, 256, f))
		{
			tisztit(segeda);
			if (!(*segeda)) continue;
			strlwr(segeda);
			if (!strncmp(segeda, S_JATEK, 7))
			{
				strcpy(jatekfn, &segeda[7]);
				jatekfn[strlen(jatekfn)-1] = 0;
				continue;
			}
			if (!strncmp(segeda, S_MENTES, 8))
			{
				strcpy(mentesfn, &segeda[8]);
				mentesfn[strlen(mentesfn)-1] = 0;
				continue;
			}
		}
	}
	return 0;
}

/* Elmenti a be†ll°t†sokat a maszk.mbf f†jlba. */
int elmentb(void)
{
	FILE *f;
	if (!(f = fopen(S_MBFN, "wt")))
	{
		return -1;
	}
	fputs(S_MB, f);
	putc('\n', f);
	fputs(S_JATEK, f);
	fputs(jatekfn, f);
	fputs("\"\n", f);
	fputs(S_MENTES, f);
	fputs(mentesfn, f);
	fputs("\"\n", f);
	fclose(f);
	return 0;
}
