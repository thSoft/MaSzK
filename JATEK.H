/* MaSzK */
/* A kalandj†tÇk-motor lelke */

/* Lev†gja s elejÇrãl Çs vÇgÇrãl a whitespace-eket, a kîzbÅlsãekbãl pedig egy space-t csin†l. */
void megtisztit(char *s)
{
	word i;
	if (*s == '\n')
	{
		*s = 0;
		return;
	}
	while ((s[0]) && ((s[0] == ' ') || (s[0] == '\t')))
	{
		strcpy(&s[0], &s[1]);
	}
	i = 0;
	while (s[i])
	{
		if ((s[i] == ' ') || (s[i] == '\t'))
		{
			s[i] = ' ';
			i++;
			while ((s[i]) && ((s[i] == ' ') || (s[i] == '\t')))
			{
				strcpy(&s[i], &s[i+1]);
			}
		}
		i++;
	}
	if (s[strlen(s)-1] == ' ') s[strlen(s)-1] = 0;
}

/* Egy kÇrdÇst tesz fel a j†tÇkosnak, a kÇrdÇs s-ben, a v†lasz r-ben van. */
void kerdez(const char *s, char *r)
{
	write(s);
	write(" ");
	gets(r);
	fflush(stdin);
	poz = 0;
	megtisztit(r);
}

/* Ki°rja a j†tÇkos inform†ci¢it. */
void jatekosinfo(void)
{
	write(aszoveg(aszereplo0(jatekos)->nev));
	writeln(" vagy.");
	korulnez();
	leltaroz();
}

/* MegkÇrdezi a j†tÇkost, hogy mit akar tenni az objektummal. c-nÇl kisebb karaktert fogad csak el.
Ha a bemenet Åres string, 0-val tÇr vissza. */
bool tettkerdes(char *s, char c)
{
	do
	{
		kerdez("Mit teszel vele?", s);
		strcpy(s, kisbetu(s));
		if ((strlen(s) == 1) && (*s >= 'a') && (*s < c)) return 1;
		if (*s)
		{
			write("Egy tett");
			writeln(" bet˚jelÇt kell be°rni!");
		}
	} while (*s);
	return 0;
}

/* MegkÇrdezi a j†tÇkost, hogy mivel akar hatni az objektumra, Çs visszatÇr a j†tÇkos †ltal v†lasztott t†rgy sorsz†m†val. */
word hataskerdes(const char *u)
{
	word i;
	Lista *p0;
	leltaroz();
	if (!szt) return MAX_TARGY+2;
	kerdez(u, segeda);
	if (!(*segeda)) return MAX_TARGY+2;
	strcpy(segeda, kisbetu(segeda));
	p0 = targy0;
	for (i = 0; i < sztargy; i++)
	{
		if (egytargy(segeda, p0) && (e_targy0->szer) && (e_targy0->hely == jatekos))
			return i;
		p0 = p0->kov;
	}
	return MAX_TARGY+1;
}

/* MegkÇrdezi a j†tÇkost, hogy mire akar hatni a t. objektummal, Çs ennek megfelelãen cselekszik. */
void hatkerdes(word t)
{
	word i;
	Lista *p0, *pe1;
	byte all, h;
	kerdez("Mire/kire akarsz hatni vele?", segeda);
	if (!(*segeda)) return;
	strcpy(segeda, kisbetu(segeda));
	p0 = targy0;
	for (i = 0; i < sztargy; i++)
	{
		if ((egytargy(segeda, p0)) && ((e_targy0->hely == aszereplo0(jatekos)->hely) || ((e_targy0->hely == jatekos) && (e_targy0->szer))))
			break;
		p0 = p0->kov;
	}
	if (i < sztargy)
	{
		if (all = e_targy0->allapot)
		{
			pe1 = atargy(i+1, all)->eszkoz;
		} else
		{
			pe1 = e_targy0->eszkoz;
		}
		while (pe1 && pe1->info)
		{
			if (t == e_esemenyp1->parameter)
			{
				kezelp(e_esemenyp1, 1);
				break;
			}
			pe1 = pe1->kov;
		}
		if (!pe1)
			writeln("Ez nem lenne cÇlravezetã.");
		return;
	}
	p0 = akadaly0;
	for (i = 0; i < szakadaly; i++)
	{
		if ((!strcmp(segeda, kisbetu(aszoveg(e_akadaly0->nev)))) && ((e_akadaly0->egyik == aszereplo0(jatekos)->hely) || (e_akadaly0->masik == aszereplo0(jatekos)->hely)))
			break;
		p0 = p0->kov;
	}
	if (i < szakadaly)
	{
		if (all = e_akadaly0->allapot)
		{
			pe1 = aakadaly(i+1, all)->eszkoz;
		} else
		{
			pe1 = e_akadaly0->eszkoz;
		}
		while (pe1 && pe1->info)
		{
			if (t == e_esemenyp1->parameter)
			{
				kezelp(e_esemenyp1, (aszereplo0(jatekos)->hely == e_akadaly0->egyik) || (aszereplo0(jatekos)->hely == e_akadaly0->masik));
				break;
			}
			pe1 = pe1->kov;
		}
		if (!pe1)
			writeln("Ez nem lenne cÇlravezetã.");
		return;
	}
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if ((egytargy(segeda, p0)) && (e_targy0->hely == aszereplo0(jatekos)->hely))
		{
			if (i+1 == jatekos)
			{
				writeln("Magadra nem hathatsz.");
				return;
			}
			break;
		}
		p0 = p0->kov;
	}
	if (i < szszereplo)
	{
		if (all = e_szereplo0->allapot)
		{
			pe1 = aszereplo(i+1, all)->eszkoz;
		} else
		{
			pe1 = e_szereplo0->eszkoz;
		}
		while (pe1 && pe1->info)
		{
			if (t == e_esemenyp1->parameter)
			{
				kezelp(e_esemenyp1, 1);
				break;
			}
			pe1 = pe1->kov;
		}
		if (!pe1)
			writeln("Ez nem lenne cÇlravezetã.");
		return;
	}
	writeln("Nincs itt semmi ilyesmi.");
}

/* MegkÇrdezi a j†tÇkost, hogy kinek akarja odaadni a t. objektumot, Çs ennek megfelelãen cselekszik. */
void adkerdes(word t)
{
	word i;
	Lista *p0, *pe1;
	byte all, h;
	kerdez("Kinek akarod odaadni?", segeda);
	if (!(*segeda)) return;
	strcpy(segeda, kisbetu(segeda));
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if ((!strcmp(segeda, kisbetu(aszoveg(e_szereplo0->nev)))) || (!strcmp(segeda, kisbetu(aszoveg(e_szereplo0->koznev)))))
		{
			if (i+1 == jatekos)
			{
				writeln("M†r n†lad van.");
				return;
			}
			if (e_szereplo0->hely == aszereplo0(jatekos)->hely) break;
		}
		p0 = p0->kov;
	}
	if (i < szszereplo)
	{
		if (all = e_szereplo0->allapot)
		{
			pe1 = aszereplo(i+1, all)->ad;
		} else
		{
			pe1 = e_szereplo0->ad;
		}
		while (pe1 && pe1->info)
		{
			if (t == e_esemenyp1->parameter)
			{
				kezelp(e_esemenyp1, 1);
				break;
			}
			pe1 = pe1->kov;
		}
		if (!pe1)
		{
			*segeda = 0;
			szereplonev(segeda, elem(szereplo0, i), 0);
			if (aszereplo0(i+1)->iranyithato)
			{
				strcat(segeda, " kîszînettel elfogadja.");
				atargy0(t)->hely = i+1;
			}
			else
			{
				strcat(segeda, " azt mondja: ");
				strcat(segeda, "\"Kîszînîm, de nincs szÅksÇgem r†.\"");
			}
			writeln(segeda);
		}
		return;
	}
	writeln("Nincs itt ilyen szereplã.");
}

/* MegkÇrdezi a j†tÇkost, hogy kinek akarja megmutatni a t. objektumot, Çs ennek megfelelãen cselekszik. */
void mutatkerdes(word t)
{
	word i;
	Lista *p0, *pe1;
	byte all, h;
	kerdez("Kinek akarod megmutatni?", segeda);
	if (!(*segeda)) return;
	strcpy(segeda, kisbetu(segeda));
	p0 = szereplo0;
	for (i = 0; i < szszereplo; i++)
	{
		if ((!strcmp(segeda, kisbetu(aszoveg(e_szereplo0->nev)))) || (!strcmp(segeda, kisbetu(aszoveg(e_szereplo0->koznev)))))
		{
			if (i+1 == jatekos)
			{
				if (all = atargy0(t)->allapot)
				{
					writeln(aszoveg(atargy(t, all)->leiras));
				} else
				{
					writeln(aszoveg(atargy0(t)->leiras));
				}
				return;
			}
			if (e_szereplo0->hely == aszereplo0(jatekos)->hely) break;
		}
		p0 = p0->kov;
	}
	if (i < szszereplo)
	{
		if (all = e_szereplo0->allapot)
		{
			pe1 = aszereplo(i+1, all)->mutat;
		} else
		{
			pe1 = e_szereplo0->mutat;
		}
		while (pe1 && pe1->info)
		{
			if (t == e_esemenyp1->parameter)
			{
				kezelp(e_esemenyp1, 1);
				break;
			}
			pe1 = pe1->kov;
		}
		if (!pe1)
		{
			*segeda = 0;
			szereplonev(segeda, elem(szereplo0, i), 0);
			strcat(segeda, " azt mondja: ");
			strcat(segeda, "\"Semmi kÇtsÇg, ez bizony ");
			targynev(segeda, elem(targy0, t-1));
			strcat(segeda, ".\"");
			writeln(segeda);
		}
		return;
	}
	writeln("Nincs itt ilyen szereplã.");
}

/* MegkÇrdezi a j†tÇkost, hogy mit akar mondani az sz. szereplãnek, Çs ennek megfelelãen cselekszik. */
void beszedkerdes(word sz)
{
	word i, j;
	Lista *p0, *pe1;
	char a[2] = "a";
	byte all;
	if (all = aszereplo0(sz)->allapot)
	{
		p0 = elem(((Lista *)(elem(szereplo, sz-1)->info)), all-1);
		pe1 = ((Szereplo *)(p0->info))->beszel;
		j = ((Szereplo *)(p0->info))->szbeszel;
	} else
	{
		p0 = elem(szereplo0, sz-1);
		pe1 = e_szereplo0->beszel;
		j = e_szereplo0->szbeszel;
	}
	for (i = 0; i < j; i++)
	{
		write(a);
		write(") ");
		writeln(aszoveg(e_esemenyp1->parameter));
		(*a)++;
		pe1 = pe1->kov;
	}
	if (*a == 'a')
	{
		writeln("Nincs semmi mondanival¢d sz†m†ra.");
		return;
	}
	do
	{
		kerdez("Mit mondasz neki?", segeda);
		strcpy(segeda, kisbetu(segeda));
		if ((strlen(segeda) == 1) && (*segeda >= 'a') && (*segeda < *a))
		{
			if (all)
			{
				pe1 = elem(((Szereplo *)(p0->info))->beszel, *segeda-'a');
			} else
			{
				pe1 = elem(e_szereplo0->beszel, *segeda-'a');
			}
			kezelp(e_esemenyp1, 1);
			break;
		} else
		{
			if (*segeda)
			{
				write("A mondanival¢");
				writeln(" bet˚jelÇt kell be°rni!");
			}
		}
	} while (*segeda);
}

/* A fãciklus. Akkor Çr vÇget, amikor vege ÇrtÇke 1 lesz. */
void fociklus(void)
{
	bool talalt = 0;
	word i, j, k;
	char a[2] = "a";
	byte all, h;
	Lista *p0, *pa, *pe1, *p;
	/* µltal†nos inform†ci¢k ki°r†sa */
	writeln("");
	if (vanbev)
	{
		strcpy(segeda, elem(szoveg, cim)->info);
		if (*segeda)
		{
			writeln(segeda);
			for (i = 0; i < strlen(segeda); i++) write("-");
			writeln("\n");
		}
		i = 0;
		while (bevezeto[i])
		{
			poz = 0;
			writeln(aszoveg(bevezeto[i]));
			if ((i < MAX_BEKEZDES-1) && (bevezeto[i+1]))
			{
				write("<Tov†bb>");
			}
			if (getchar() != '\n')
			{
				fflush(stdin);
				writeln("");
				break;
			}
			fflush(stdin);
			i++;
		}
	}
	jatekosinfo();
	/* ParancsÇrtelmezã ciklus */
	while (!vege)
	{
		/* Parancs beolvas†sa */
		write(">");
		strcpy(segeda, parancs);
		gets(parancs);
		fflush(stdin);
		poz = 0;
		if (!strcmp(parancs, "-"))
		{
			strcpy(parancs, segeda);
		}
		if (!parancs[0]) continue;
		megtisztit(parancs);
		strcpy(parancs, kisbetu(parancs));
		talalt = 0;
		leptet = 1;
		/* A 6 passz°v parancs egyike? */
		for (i = 0; i < SZ_PARANCS*2; i++)
		{
			if (!strcmp(parancs, parancsok[i]))
			{
				talalt = 1;
				if (i/2 >= 3) leptet = 0;
				pk[i/2]();
				break;
			}
		}
		/* Egy ir†ny? */
		if (!talalt)
		{
			for (i = 0; i < SZ_IRANY*2; i++)
			{
				if (!strcmp(parancs, iranyok[i]))
				{
					talalt = 1;
					mozog(i/2);
					break;
				}
			}
		}
		/* Egy j†tÇkos sorsz†ma? */
		if (!talalt)
		{
			if ((j = atoi(parancs)) && (j <= szjatekos))
			{
				talalt = 1;
				leptet = 0;
				p0 = szereplo0;
				k = 0;
				for (i = 0; i < szszereplo; i++)
				{
					if ((e_szereplo0->iranyithato) && (e_szereplo0->hely)) k++;
					if (k == j)
					{
						jatekos = i+1;
						jatekosinfo();
						if (all = aszereplo0(jatekos)->allapot)
						{
							kezel(&(aszereplo(jatekos, all)->iranyit), 1);
						} else
						{
							kezel(&(aszereplo0(jatekos)->iranyit), 1);
						}
						break;
					}
					p0 = p0->kov;
				}
				if (k != j) talalt = 0;
			}
		}
		/* Egy elÇrhetã t†rgy? */
		if (!talalt)
		{
			h = aszereplo0(jatekos)->hely;
			p0 = targy0;
			for (i = 0; i < sztargy; i++)
			{
				if (egytargy(parancs, p0))
				{
					if (e_targy0->szer)
					{
						if (e_targy0->hely != jatekos)
						{
							p0 = p0->kov;
							continue;
						}
					} else
					{
						if (e_targy0->hely != h)
						{
							p0 = p0->kov;
							continue;
						}
					}
					if (all = e_targy0->allapot)
					{
						strcpy(seged, aszoveg(atargy(i+1, all)->leiras));
					} else
					{
						strcpy(seged, aszoveg(e_targy0->leiras));
					}
					if (sotetvan())
					{
						writeln("A nagy sîtÇtben nem l†tod.");
					} else
					{
						if (*seged) writeln(seged);
						if (all)
						{
							kezel(&(atargy(i+1, all)->vizsgal), 1);
						} else
						{
							kezel(&(e_targy0->vizsgal), 1);
						}
					}
					pa = p0;
					k = i+1;
					talalt = 1;
					break;
				}
				p0 = p0->kov;
			}
			if (talalt)
			{
				p0 = pa;
				writeln("a) Hatok r† valamivel");
				*a = 'b';
				if (!e_targy0->rogzitett)
				{
					if (e_targy0->szer)
					{
						writeln("b) Leteszem");
						writeln("c) Hatok vele valamire/valakire");
						writeln("d) Odaadom valakinek");
						writeln("e) Megmutatom valakinek");
						*a = 'f';
					} else
					{
						writeln("b) Felveszem");
						*a = 'c';
					}
				}
				if (e_targy0->allapot)
				{
					pa = elem(((Lista *)(elem(targy, k-1)->info)), e_targy0->allapot-1);
					pe1 = e_targya->akcio;
					for (i = 0; i < e_targya->szakcio; i++)
					{
						strcpy(seged, " ) ");
						*seged = *a+i;
						strcat(seged, aszoveg(e_esemenyp1->parameter));
						writeln(seged);
						pe1 = pe1->kov;
					}
				} else
				{
					pe1 = e_targy0->akcio;
					for (i = 0; i < e_targy0->szakcio; i++)
					{
						strcpy(seged, " ) ");
						*seged = *a+i;
						strcat(seged, aszoveg(e_esemenyp1->parameter));
						writeln(seged);
						pe1 = pe1->kov;
					}
				}
				if (tettkerdes(segeda, *a+i))
				{
					if (*segeda == 'a')
					{
						j = hataskerdes("Mivel akarsz hatni r†?");
						if (j > MAX_TARGY)
						{
							if (j == MAX_TARGY+1) writeln("Nincs ilyen t†rgy n†lad.");
						}
						else
						{
							if (all = e_targy0->allapot)
							{
								pe1 = atargy(k, all)->eszkoz;
							} else
							{
								pe1 = atargy0(k)->eszkoz;
							}
							while (pe1 && pe1->info)
							{
								if (j+1 == e_esemenyp1->parameter)
								{
									kezelp(e_esemenyp1, 1);
									break;
								}
								pe1 = pe1->kov;
							}
							if (!pe1)
								writeln("Ez nem lenne cÇlravezetã.");
						}
					}
					else
					{
						if (!e_targy0->rogzitett)
						{
							if (e_targy0->szer)
							{
								switch (*segeda)
								{
									case 'b':
									{
										if (e_targy0->allapot)
										{
											pa = elem(((Lista *)(elem(targy, k-1)->info)), e_targy0->allapot-1);
											e_targy0->szer = 0;
											e_targy0->hely = aszereplo0(jatekos)->hely;
											if (!(e_targya->letesz.uzenet)) writeln("Elãveszed Çs lerakod.");
											kezel(&(e_targya->letesz), 1);
										} else
										{
											e_targy0->szer = 0;
											e_targy0->hely = aszereplo0(jatekos)->hely;
											if (!(e_targy0->letesz.uzenet)) writeln("Elãveszed Çs lerakod.");
											kezel(&(e_targy0->letesz), 1);
										}
										break;
									}
									case 'c':
									{
										hatkerdes(k);
										break;
									}
									case 'd':
									{
										adkerdes(k);
										break;
									}
									case 'e':
									{
										mutatkerdes(k);
										break;
									}
									default:
									{
										if (all = e_targy0->allapot)
										{
											pe1 = elem(atargy(k, all)->akcio, *segeda-*a);
										} else
										{
											pe1 = elem(atargy0(k)->akcio, *segeda-*a);
										}
										kezelp(e_esemenyp1, 1);
									}
								}
							} else
							{
								if (*segeda == 'b')
								{
									if (e_targy0->allapot)
									{
										pa = elem(((Lista *)(elem(targy, k-1)->info)), e_targy0->allapot-1);
										e_targy0->szer = 1;
										e_targy0->hely = jatekos;
										if (!(e_targya->felvesz.uzenet)) writeln("Felveszed Çs elteszed.");
										kezel(&(e_targya->felvesz), 1);
									} else
									{
										e_targy0->szer = 1;
										e_targy0->hely = jatekos;
										if (!(e_targy0->felvesz.uzenet)) writeln("Felveszed Çs elteszed.");
										kezel(&(e_targy0->felvesz), 1);
									}
								}
								else
								{
									if (all = e_targy0->allapot)
									{
										pe1 = elem(atargy(k, all)->akcio, *segeda-*a);
									} else
									{
										pe1 = elem(atargy0(k)->akcio, *segeda-*a);
									}
									kezelp(e_esemenyp1, 1);
								}
							}
						} else
						{
							if (all = e_targy0->allapot)
							{
								pe1 = elem(atargy(k, all)->akcio, *segeda-*a);
							} else
							{
								pe1 = elem(atargy0(k)->akcio, *segeda-*a);
							}
							kezelp(e_esemenyp1, 1);
						}
					}
				}
			}
		}
		/* Egy elÇrhetã akad†ly? */
		if (!talalt)
		{
			h = aszereplo0(jatekos)->hely;
			p0 = akadaly0;
			for (i = 0; i < szakadaly; i++)
			{
				if ((!strcmp(parancs, kisbetu(aszoveg(e_akadaly0->nev)))))
				{
					if (!((e_akadaly0->egyik == h) || (e_akadaly0->masik == h)))
					{
						p0 = p0->kov;
						continue;
					}
					if (all = e_akadaly0->allapot)
					{
						strcpy(seged, aszoveg(aakadaly(i+1, all)->leiras));
					} else
					{
						strcpy(seged, aszoveg(e_akadaly0->leiras));
					}
					if (sotetvan())
					{
						writeln("A nagy sîtÇtben nem l†tod.");
					} else
					{
						if (*seged) writeln(seged);
						if (all)
						{
							kezel(&(aakadaly(i+1, all)->vizsgal), 1);
						} else
						{
							kezel(&(e_akadaly0->vizsgal), 1);
						}
					}
					pa = p0;
					k = i+1;
					talalt = 1;
					break;
				}
				p0 = p0->kov;
			}
			if (talalt)
			{
				p0 = pa;
				writeln("a) Hatok r† valamivel");
				*a = 'b';
				if (e_akadaly0->allapot)
				{
					pa = elem(((Lista *)(elem(akadaly, k-1)->info)), e_akadaly0->allapot-1);
					pe1 = e_akadalya->akcio;
					for (i = 0; i < e_akadalya->szakcio; i++)
					{
						strcpy(seged, " ) ");
						*seged = *a+i;
						strcat(seged, aszoveg(e_esemenyp1->parameter));
						writeln(seged);
						pe1 = pe1->kov;
					}
				} else
				{
					pe1 = e_akadaly0->akcio;
					for (i = 0; i < e_akadaly0->szakcio; i++)
					{
						strcpy(seged, " ) ");
						*seged = *a+i;
						strcat(seged, aszoveg(e_esemenyp1->parameter));
						writeln(seged);
						pe1 = pe1->kov;
					}
				}
				if (tettkerdes(segeda, *a+i))
				{
					if (*segeda == 'a')
					{
						j = hataskerdes("Mivel akarsz hatni r†?");
						if (j > MAX_TARGY)
						{
							if (j == MAX_TARGY+1) writeln("Nincs ilyen t†rgy n†lad.");
						}
						else
						{
							if (all = e_akadaly0->allapot)
							{
								pe1 = aakadaly(k, all)->eszkoz;
							} else
							{
								pe1 = aakadaly0(k)->eszkoz;
							}
							while (pe1 && pe1->info)
							{
								if (j+1 == e_esemenyp1->parameter)
								{
									kezelp(e_esemenyp1, 1);
									break;
								}
								pe1 = pe1->kov;
							}
							if (!pe1)
								writeln("Ez nem lenne cÇlravezetã.");
						}
					}
					else
					{
						if (all = e_akadaly0->allapot)
						{
							pe1 = elem(aakadaly(k, all)->akcio, *segeda-*a);
						} else
						{
							pe1 = elem(aakadaly0(k)->akcio, *segeda-*a);
						}
						kezelp(e_esemenyp1, 1);
					}
				}
			}
		}
		/* Egy elÇrhetã szereplã? */
		if (!talalt)
		{
			h = aszereplo0(jatekos)->hely;
			p0 = szereplo0;
			for (i = 0; i < szszereplo; i++)
			{
				if ((!strcmp(parancs, kisbetu(aszoveg(e_szereplo0->nev)))) || (!strcmp(parancs, kisbetu(aszoveg(e_szereplo0->koznev)))))
				{
					if (e_szereplo0->hely != h)
					{
						p0 = p0->kov;
						continue;
					}
					if (all = e_szereplo0->allapot)
					{
						strcpy(seged, aszoveg(aszereplo(i+1, all)->leiras));
					} else
					{
						strcpy(seged, aszoveg(e_szereplo0->leiras));
					}
					if (sotetvan())
					{
						writeln("A nagy sîtÇtben nem l†tod.");
					} else
					{
						if (*seged) writeln(seged);
						if (all)
						{
							kezel(&(aszereplo(i+1, all)->vizsgal), 1);
						} else
						{
							kezel(&(e_szereplo0->vizsgal), 1);
						}
					}
					pa = p0;
					k = i+1;
					talalt = 1;
					break;
				}
				p0 = p0->kov;
			}
			if (talalt)
			{
				if (k == jatekos)
				{
					write(aszoveg(aszereplo0(jatekos)->nev));
					writeln(" vagy.");
				}
				else
				{
					p0 = pa;
					writeln("a) Hatok r† valamivel");
					writeln("b) BeszÇlek vele");
					writeln("c) Odaadok neki valamit");
					writeln("d) Megmutatok neki valamit");
					if (e_szereplo0->iranyithato)
					{
						writeln("e) Ir†ny°tom");
						*a = 'f';
					} else
					{
						*a = 'e';
					}
					if (e_szereplo0->allapot)
					{
						pa = elem(((Lista *)(elem(szereplo, k-1)->info)), e_szereplo0->allapot-1);
						pe1 = e_szereploa->akcio;
						for (i = 0; i < e_szereploa->szakcio; i++)
						{
							strcpy(seged, " ) ");
							*seged = *a+i;
							strcat(seged, aszoveg(e_esemenyp1->parameter));
							writeln(seged);
							pe1 = pe1->kov;
						}
					} else
					{
						pe1 = e_szereplo0->akcio;
						for (i = 0; i < e_szereplo0->szakcio; i++)
						{
							strcpy(seged, " ) ");
							*seged = *a+i;
							strcat(seged, aszoveg(e_esemenyp1->parameter));
							writeln(seged);
							pe1 = pe1->kov;
						}
					}
					if (tettkerdes(segeda, *a+i))
					{
						if (*segeda == 'a')
						{
							j = hataskerdes("Mivel akarsz hatni r†?");
							if (j > MAX_TARGY)
							{
								if (j == MAX_TARGY+1) writeln("Nincs ilyen t†rgy n†lad.");
							}
							else
							{
								if (all = e_szereplo0->allapot)
								{
									pe1 = aszereplo(k, all)->eszkoz;
								} else
								{
									pe1 = aszereplo0(k)->eszkoz;
								}
								while (pe1 && pe1->info)
								{
									if (j+1 == e_esemenyp1->parameter)
									{
										kezelp(e_esemenyp1, 1);
										break;
									}
									pe1 = pe1->kov;
								}
								if (!pe1)
									writeln("Ez nem lenne cÇlravezetã.");
							}
						}
						else
						{
							switch (*segeda)
							{
								case 'b':
								{
									beszedkerdes(k);
									break;
								}
								case 'c':
								{
									j = hataskerdes("Mit akarsz neki odaadni?");
									if (j > MAX_TARGY)
									{
										if (j == MAX_TARGY+1) writeln("Nincs ilyen t†rgy n†lad.");
									}
									else
									{
										if (all = e_szereplo0->allapot)
										{
											pe1 = aszereplo(k, all)->ad;
										} else
										{
											pe1 = aszereplo0(k)->ad;
										}
										while (pe1 && pe1->info)
										{
											if (j+1 == e_esemenyp1->parameter)
											{
												kezelp(e_esemenyp1, 1);
												break;
											}
											pe1 = pe1->kov;
										}
										if (!pe1)
										{
											*segeda = 0;
											szereplonev(segeda, elem(szereplo0, k-1), 0);
											if (aszereplo0(k)->iranyithato)
											{
												strcat(segeda, " kîszînettel elfogadja.");
												atargy0(j+1)->hely = k;
											}
											else
											{
												strcat(segeda, " azt mondja: ");
												strcat(segeda, "\"Kîszînîm, de nincs szÅksÇgem r†.\"");
											}
											writeln(segeda);
										}
									}
									break;
								}
								case 'd':
								{
									j = hataskerdes("Mit akarsz neki megmutatni?");
									if (j > MAX_TARGY)
									{
										if (j == MAX_TARGY+1) writeln("Nincs ilyen t†rgy n†lad.");
									}
									else
									{
										if (all = e_szereplo0->allapot)
										{
											pe1 = aszereplo(k, all)->mutat;
										} else
										{
											pe1 = aszereplo0(k)->mutat;
										}
										while (pe1 && pe1->info)
										{
											if (j+1 == e_esemenyp1->parameter)
											{
												kezelp(e_esemenyp1, 1);
												break;
											}
											pe1 = pe1->kov;
										}
										if (!pe1)
										{
											*segeda = 0;
											szereplonev(segeda, elem(szereplo0, k-1), 0);
											strcat(segeda, " azt mondja: ");
											strcat(segeda, "\"Semmi kÇtsÇg, ez bizony ");
											targynev(segeda, elem(targy0, j));
											strcat(segeda, ".\"");
											writeln(segeda);
										}
									}
									break;
								}
								default:
								{
									if ((e_szereplo0->iranyithato) && (*segeda == 'e'))
									{
										jatekos = k;
										jatekosinfo();
										if (all = aszereplo0(jatekos)->allapot)
										{
											kezel(&(aszereplo(jatekos, all)->iranyit), 1);
										} else
										{
											kezel(&(aszereplo0(jatekos)->iranyit), 1);
										}
										leptet = 0;
										pe1 = NULL;
									}
									else
									{
										if (all = e_szereplo0->allapot)
										{
											pe1 = elem(aszereplo(k, all)->akcio, *segeda-*a);
										} else
										{
											pe1 = elem(aszereplo0(k)->akcio, *segeda-*a);
										}
										kezelp(e_esemenyp1, 1);
									}
								}
							}
						}
					}
				}
			}
		}
		/* Ismeretlen parancs */
		if (!talalt)
		{
			if (elso)
			{
				writeln("Ismeretlen parancs!");
				writeln("÷rd be az †ltalad kîvetni k°v†nt ir†nyt, egy elÇrhetã t†rgy vagy szereplã nevÇt, az ir†ny°tand¢ j†tÇkos sorsz†m†t, vagy az al†bbi parancsok egyikÇt:");
				*seged = 0;
				for (i = 0; i < SZ_PARANCS; i++)
				{
					strcat(seged, parancsok[i*2]);
					strcat(seged, " (");
					strcat(seged, parancsok[i*2+1]);
					strcat(seged, "), ");
				}
				seged[strlen(seged)-2] = 0;
				writeln(seged);
				elso = 0;
			}
			else
			{
				writeln("Ismeretlen parancs!");
			}
		} else
		{
			if (leptet)
			{
				p0 = helyiseg0;
				for (i = 0; i < szhelyiseg; i++)
				{
					if (e_helyiseg0->ido)
					{
						e_helyiseg0->ido--;
						if (!(e_helyiseg0->ido))
						{
							if (all = e_helyiseg0->allapot)
							{
								kezelp(&(ahelyiseg(i+1, all)->lejar), (ahelyiseg(i+1, all)->lejar.parameter) || (aszereplo0(jatekos)->hely == i+1));
							} else
							{
								kezelp(&(e_helyiseg0->lejar), (e_helyiseg0->lejar.parameter) || (aszereplo0(jatekos)->hely == i+1));
							}
						}
					}
					p0 = p0->kov;
				}
				p0 = targy0;
				for (i = 0; i < sztargy; i++)
				{
					if (e_targy0->ido)
					{
						e_targy0->ido--;
						if (!(e_targy0->ido))
						{
							if (all = e_targy0->allapot)
							{
								kezelp(&(atargy(i+1, all)->lejar), (atargy(i+1, all)->lejar.parameter) || ((!(e_targy0->szer)) && (aszereplo0(jatekos)->hely == e_targy0->hely)) || ((e_targy0->szer) && (e_targy0->hely == jatekos)));
							} else
							{
								kezelp(&(e_targy0->lejar), (e_targy0->lejar.parameter) || ((!(e_targy0->szer)) && (aszereplo0(jatekos)->hely == e_targy0->hely)) || ((e_targy0->szer) && (e_targy0->hely == jatekos)));
							}
						}
					}
					p0 = p0->kov;
				}
				p0 = akadaly0;
				for (i = 0; i < szakadaly; i++)
				{
					if (e_akadaly0->ido)
					{
						e_akadaly0->ido--;
						if (!(e_akadaly0->ido))
						{
							if (all = e_akadaly0->allapot)
							{
								kezelp(&(aakadaly(i+1, all)->lejar), (aakadaly(i+1, all)->lejar.parameter) || (aszereplo0(jatekos)->hely == aakadaly0(i+1)->egyik) || (aszereplo0(jatekos)->hely == aakadaly0(i+1)->masik));
							} else
							{
								kezelp(&(e_akadaly0->lejar), (e_akadaly0->lejar.parameter) || (aszereplo0(jatekos)->hely == e_akadaly0->egyik) || (aszereplo0(jatekos)->hely == e_akadaly0->masik));
							}
						}
					}
					p0 = p0->kov;
				}
				p0 = szereplo0;
				for (i = 0; i < szszereplo; i++)
				{
					if (i+1 != jatekos)
					{
						if (all = e_szereplo0->allapot)
						{
							kezelp(&(aszereplo(i+1, all)->lep), (aszereplo(i+1, all)->lep.parameter) || (aszereplo0(jatekos)->hely == aszereplo0(i+1)->hely));
						} else
						{
							kezelp(&(e_szereplo0->lep), (e_szereplo0->lep.parameter) || (aszereplo0(jatekos)->hely == e_szereplo0->hely));
						}
					}
					if (e_szereplo0->ido)
					{
						e_szereplo0->ido--;
						if (!(e_szereplo0->ido))
						{
							if (all = e_szereplo0->allapot)
							{
								kezelp(&(aszereplo(i+1, all)->lejar), (aszereplo(i+1, all)->lejar.parameter) || (aszereplo0(jatekos)->hely == aszereplo0(i+1)->hely));
							} else
							{
								kezelp(&(e_szereplo0->lejar), (e_szereplo0->lejar.parameter) || (aszereplo0(jatekos)->hely == e_szereplo0->hely));
							}
						}
					}
					p0 = p0->kov;
				}
			}
		}
	}
}
