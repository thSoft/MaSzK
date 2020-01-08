/* MaSzK */
/* µltal nos seg‚dfggv‚nyek */

/* Konstansok */

#define SORHOSSZ 80
#define STRHOSSZ 2048
#define U_MEM "Nincs el‚g mem¢ria!"
#define U_FAJL "A megadott f jl nem l‚tezik vagy nem olvashat¢!"

/* V ltoz¢k */

char *segedb, *segedc;
signed char poz = 0;
char temp[33];

/* T¡pusok */

typedef unsigned char bool, byte;
typedef unsigned int word;
typedef unsigned long dword;

typedef struct lista_t
{
	void *info;
	struct lista_t *kov;
} Lista;

/* Protot¡pusok */

void write(const char *s);
void writeln(const char *s);
void vilagvege(void);
int elment(char *s);
int elmentb(void);
int betoltm(char *s);
void korulnez(void);

/* Fggv‚nyek */

/* s hibazenettel kil‚p a programb¢l, -1 kil‚p‚si k¢ddal. */
void hiba(const char *s)
{
	if (*s)
	{
		write("Hiba: ");
		writeln(s);
	}
	vilagvege();
	exit(-1);
}

/* Megsz molja, hogy a c karakter h nyszor fordul el‹ az s stringben. */
word count(const char *s, char c)
{
	word i = 0;
	while (*s)
	{
		if (*s == c) i++;
		s++;
	}
	return i;
}

/* Ki¡rja s-t a szabv nyos kimenetre sort”r‚ssel.
A sorhosszt a SORHOSSZ  lland¢ hat rozza meg. */
void write(const char *s)
{
	char *h;
	while (*s)
	{
		if (*s == ' ')
		{
			if (!(h = strchr(s+1, ' ')))
			{
				if (strchr(s+1, 0)-s > SORHOSSZ-poz)
				{
					if (poz < SORHOSSZ) putchar('\n');
					s++;
					poz = 0;
					continue;
				}
			}
			else
			{
				if (h-s > SORHOSSZ-poz)
				{
					if (poz < SORHOSSZ) putchar('\n');
					s++;
					poz = 0;
					continue;
				}
			}
		}
		if ((poz > SORHOSSZ) || (*s == '\n')) poz = -1;
		putchar(*s);
		s++;
		poz++;
	}
}

/* Ki¡rja s-t a szabv nyos kimenetre sort”r‚ssel, £jsor karakterrel a v‚g‚n. */
void writeln(const char *s)
{
	write(s);
	if (poz != SORHOSSZ)
	{
		putchar('\n');
		poz = 0;
	}
}

/* s kisbetûs alakj val t‚r vissza (a magyar ‚kezetes karaktereket is  talak¡tja). */
char *kisbetu(const char *s)
{
	int i = 0;
	char *p;
	char nagy[] = "µÖà™Šéšë", kicsi[] = " ‚¡¢”‹£û";
	strcpy(segedb, s);
	while (segedb[i])
	{
		if ((segedb[i] >= 'A') && (segedb[i] <= 'Z'))
		{
			segedb[i] += 32;
		}
		else
		{
			if (p = strchr(nagy, segedb[i]))
			{
				segedb[i] = kicsi[p-nagy];
			}
		}
		i++;
	}
	return segedb;
}

/* Eld”nti, hogy a megadott string decim lis sz m-e. */
bool szam(const char *s)
{
	word i = 0;
	while (s[i])
	{
		if (!isdigit(s[i])) return 0;
		i++;
	}
	return 1;
}

/* Stringg‚ alak¡t egy sz mot. */
char *itostr(dword x)
{
	return ultoa(x, temp, 10);
}

/* Eld”nti, hogy a megadott karakter magyar mag nhangz¢-e. */
bool mgh(char c)
{
	char s[] = "a e‚i¡o¢”‹u£ûAµEIÖOà™ŠUéšë";
	return (strchr(s, c) != 0);
}

/* Feltesz egy eld”ntend‹ k‚rd‚st a felhaszn l¢nak.
Visszat‚r‚si ‚rt‚ke: a felhaszn l¢ igennel felelt-e. */
bool kerdes(char *s)
{
	write(s);
	write(" ");
	gets(segedc);
	fflush(stdin);
	poz = 0;
	strcpy(segedc, kisbetu(segedc));
	return ((!strcmp(segedc, "i")) || (!strcmp(segedc, "igen")));
}

/* L‚trehozza egy list els‹ elem‚t. */
Lista *letrehoz(Lista *l)
{
	if (!(l = (Lista *)malloc(sizeof(Lista)))) hiba(U_MEM);
	l->info = NULL;
	l->kov = NULL;
	return l;
}

/* T”r”l egy list t. */
void torol(Lista *l)
{
	Lista *s;
	while (l)
	{
		s = l->kov;
		if (l->info) free(l->info);
		free(l);
		l = s;
	}
}

/* Visszaadja egy lista n. elem‚t. */
Lista *elem(Lista *l, word n)
{
	word i = 0;
	while (l)
	{
		if (i == n) return l;
		i++;
		l = l->kov;
	}
	return NULL;
}

/* Besz£r egy elemet egy megadott listaelem m”g‚, ‚s az arra mutat¢ pointerrel t‚r vissza. */
Lista *beszur(Lista *l)
{
	Lista *e;
	e = letrehoz(e);
	l->kov = e;
	return e;
}
