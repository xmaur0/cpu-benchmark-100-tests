#include <windows.h>
#include <richedit.h>
#include <wininet.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <random>
#include <future>
#include <string>
#include <sstream>
#include <cstdio>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <stack>
#include <iomanip>
#include <exception>
#include <atomic>
#include <numeric>
#pragma comment(lib, "wininet.lib")

#ifndef FW_MEDIUM
#define FW_MEDIUM 500
#endif
#ifndef CFM_WEIGHT
#define CFM_WEIGHT 0x00400000
#endif
#ifndef CFM_BACKCOLOR
#define CFM_BACKCOLOR 0x04000000
#endif
#ifndef EM_SETREADONLY
#define EM_SETREADONLY (WM_USER + 207)
#endif
#ifndef EM_GETSCROLLPOS
#define EM_GETSCROLLPOS (WM_USER + 221)
#endif
#ifndef EM_SETSCROLLPOS
#define EM_SETSCROLLPOS (WM_USER + 222)
#endif

#define ID_BTN_RUN 101
#define ID_COMBO_LANG 102
#define ID_COMBO_PC_COMPARE 103
#define ID_COMBO_FONT 106
#define ID_EDIT_LOG 104
#define ID_STATIC_LANG 201
#define ID_STATIC_COMPARE 202
#define ID_STATIC_STATUS 203
#define ID_STATIC_FONT 204
#define ID_COMBO_CPU_A 109
#define ID_COMBO_CPU_B 110
#define ID_STATIC_CPU_A 207
#define ID_STATIC_CPU_B 208
#define ID_BTN_RESUMO 111
#define ID_BTN_VER_RESULTADO 112
#define ID_BTN_RANKING 113
#define ID_MODAL_BTN_CLOSE 301
#define ID_RANKING_BTN_CLOSE 401

const wchar_t* NPOINT_DOC_ID = L"0605457d8b57e27e40a9";
std::wstring GetNpointUrl() { return L"https://api.npoint.io/" + std::wstring(NPOINT_DOC_ID); }
std::wstring GetNpointPath() { return L"/" + std::wstring(NPOINT_DOC_ID); }

struct IdiomaTextos {
const wchar_t* tituloJanela; const wchar_t* labelLang; const wchar_t* labelCompare;
const wchar_t* labelFont; const wchar_t* btnRun; const wchar_t* statusPronto;
const wchar_t* statusRodandoMulti; const wchar_t* statusRodandoSingle;
const wchar_t* headerResult; const wchar_t* lblThreads; const wchar_t* colTeste;
const wchar_t* colSeuPC; const wchar_t* colOutroPC; const wchar_t* colDif;
const wchar_t* colPontuacao; const wchar_t* selecionePC; const wchar_t* avisoRodarPrimeiro;
const wchar_t* compMultiCore; const wchar_t* compSingleCore; const wchar_t* compTotal;
const wchar_t* msgMaisRapido; const wchar_t* msgMaisLento; const wchar_t* msgEmpate;
const wchar_t* msgSelecioneParaComparar; const wchar_t* tituloErro;
const wchar_t* msgErroBenchmark; const wchar_t* msgErroDesconhecido;
const wchar_t* statusErroBenchmark; const wchar_t* tituloAguarde;
const wchar_t* msgAguardeFechar; const wchar_t* labelCpuA; const wchar_t* labelCpuB;
const wchar_t* btnResumo; const wchar_t* btnVerResultado; const wchar_t* modalVs;
const wchar_t* modalMaisRapido; const wchar_t* modalFechar;
const wchar_t* modalMultiCore; const wchar_t* modalSingleCore;
const wchar_t* modalPts; const wchar_t* modalGanhou; const wchar_t* modalTestes;
const wchar_t* btnRanking; const wchar_t* rankingTitulo; const wchar_t* rankingFechar;
};

const wchar_t* nomesTestesPT[100] = {
L"01. Ponto Flutuante",L"02. Matriz Inteiros",L"03. Ordenacao Dados",L"04. Numeros Primos",
L"05. Alocacao Heap",L"06. Operacoes Bitwise",L"07. Funcao Hash",L"08. Estresse Cache",
L"09. Polinomios",L"10. Logica Arrays",L"11. Criptografia SHA",L"12. Compressao RLE",
L"13. Fisica N-Corpos",L"14. Simulacao Vida",L"15. Sintese Audio",
L"16. Processamento Rede",L"17. IA Perceptron",L"18. Busca Database",
L"19. Render Particulas",L"20. Steganografia LSB",L"21. Fractal Mandelbrot",
L"22. Transformada Fourier",L"23. Caminho Minimo",L"24. Compilador Regex",L"25. Motor XML",
L"26. Multiplicacao Matriz",L"27. Ray Tracing Simples",L"28. Algoritmo Genetico",
L"29. Simulacao Fluidos",L"30. Cifra AES Simulada",L"31. Pathfinding A*",
L"32. Monte Carlo Pi",L"33. Convolucao Imagem",L"34. Arvore B-Tree",L"35. Calculo Tensorial",
L"36. Fatorial Recursivo",L"37. Sequencia Fibonacci",L"38. Torre de Hanoi",
L"39. Crivo de Eratostenes",L"40. MDC Euclides",L"41. Potencia Modular",
L"42. Raiz Quadrada Newton",L"43. Seno Taylor Series",L"44. Exponencial Math",
L"45. Logaritmo Natural",L"46. Valor Absoluto Bulk",L"47. Arredondamento Bulk",
L"48. Clamp Values",L"49. Lerp Linear",L"50. Spline Cubica",
L"51. Bubble Sort",L"52. Insertion Sort",L"53. Selection Sort",
L"54. Quick Sort Pivot",L"55. Merge Sort",L"56. Heap Sort",
L"57. Counting Sort",L"58. Radix Sort",L"59. Bucket Sort",
L"60. Shell Sort",L"61. String Copy",L"62. String Concat",
L"63. String Compare",L"64. String Find",L"65. String Reverse",
L"66. String To Upper",L"67. String Trim",L"68. CSV Parse",
L"69. JSON Tokenizer",L"70. Base64 Encode",L"71. Hex Dump",
L"72. Checksum CRC32",L"73. Adler32 Check",L"74. Fletcher Checksum",
L"75. XOR Cipher",L"76. ROT13 Cipher",L"77. Caesar Cipher",
L"78. Vigenere Cipher",L"79. Random Fill",L"80. Memory Set",
L"81. Memory Move",L"82. Vector Add",L"83. Vector Dot Product",
L"84. Vector Cross Product",L"85. Matrix Determinant",L"86. Matrix Inverse",
L"87. Linked List Traverse",L"88. Binary Search Tree",L"89. Hash Map Ops",
L"90. Priority Queue",L"91. Stack Push Pop",L"92. Queue Enqueue Dequeue",
L"93. Graph DFS",L"94. Graph BFS",L"95. Dijkstra Simple",
L"96. Floyd Warshall",L"97. Knapsack DP",L"98. LCS Dynamic",
L"99. Edit Distance",L"100. Prime Factorization"
};

IdiomaTextos traducoes[] = {
{ L"Benchmark Multi-Core C++",L"Idioma:",L"Comparar com:",L"Fonte:",L"Iniciar Benchmark",L"Pronto.",L"Executando MULTI-CORE...",L"Executando SINGLE-CORE...",L"RESULTADO FINAL (100 TESTES)",L"Nucleos: ",L"Teste",L"Seu PC",L"Outro PC",L"Dif",L"Pts",L"Selecione um PC...",L"Execute o benchmark primeiro.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** SEU PC E MAIS RAPIDO (+",L"*** SEU PC E MAIS LENTO (",L"*** EMPATE TECNICO ***",L"*** SELECIONE UM PC PARA VER A COMPARACAO ***",L"Erro",L"Erro durante o benchmark.",L"Erro desconhecido.",L"Erro no benchmark.",L"Aguarde",L"Aguarde o termino antes de fechar.",L"CPU A:",L"CPU B:",L"\x26A1 RESUMO",L"\x26A1 VER RESULTADO",L"VS",L"E MAIS RAPIDO",L"FECHAR",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Ganhou:",L"testes",L"\x2605 RANKING",L"RANKING GLOBAL",L"FECHAR" },
{ L"C++ Multi-Core Benchmark",L"Language:",L"Compare with:",L"Font:",L"Start Benchmark",L"Ready.",L"Running MULTI-CORE...",L"Running SINGLE-CORE...",L"FINAL SCORE (100 TESTS)",L"Cores: ",L"Test",L"Your PC",L"Other PC",L"Diff",L"Score",L"Select a PC...",L"Run benchmark first.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** YOUR PC IS FASTER (+",L"*** YOUR PC IS SLOWER (",L"*** TECHNICAL TIE ***",L"*** SELECT A PC TO COMPARE ***",L"Error",L"Benchmark error.",L"Unknown error.",L"Benchmark error.",L"Wait",L"Wait for benchmark to finish.",L"CPU A:",L"CPU B:",L"\x26A1 SUMMARY",L"\x26A1 VIEW RESULT",L"VS",L"IS FASTER",L"CLOSE",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Won:",L"tests",L"\x2605 RANKING",L"GLOBAL RANKING",L"CLOSE" },
{ L"Benchmark Multi-Core C++",L"Idioma:",L"Comparar con:",L"Fuente:",L"Iniciar",L"Listo.",L"Ejecutando MULTI-CORE...",L"Ejecutando SINGLE-CORE...",L"PUNTUACION FINAL",L"Nucleos: ",L"Prueba",L"Tu PC",L"Otro PC",L"Dif",L"Pts",L"Selecciona un PC...",L"Ejecuta el benchmark primero.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** TU PC ES MAS RAPIDA (+",L"*** TU PC ES MAS LENTA (",L"*** EMPATE ***",L"*** SELECCIONA UN PC ***",L"Error",L"Error en benchmark.",L"Error desconocido.",L"Error.",L"Espera",L"Espera a que termine.",L"CPU A:",L"CPU B:",L"\x26A1 RESUMEN",L"\x26A1 VER RESULTADO",L"VS",L"ES MAS RAPIDA",L"CERRAR",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gano:",L"pruebas",L"\x2605 RANKING",L"RANKING GLOBAL",L"CERRAR" },
{ L"Test C++ Multi-Core",L"Langue:",L"Comparer:",L"Police:",L"Demarrer",L"Pret.",L"Tests MULTI-CORE...",L"Tests SINGLE-CORE...",L"SCORE FINAL",L"Coeurs: ",L"Test",L"Votre PC",L"Autre PC",L"Diff",L"Score",L"Selectionnez un PC...",L"Lancez le benchmark.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** VOTRE PC EST PLUS RAPIDE (+",L"*** VOTRE PC EST PLUS LENT (",L"*** EGALITE ***",L"*** SELECTIONNEZ UN PC ***",L"Erreur",L"Erreur benchmark.",L"Erreur inconnue.",L"Erreur.",L"Patientez",L"Attendez la fin du test.",L"CPU A :",L"CPU B :",L"\x26A1 RESUME",L"\x26A1 VOIR RESULTAT",L"VS",L"EST PLUS RAPIDE",L"FERMER",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gagne:",L"tests",L"\x2605 CLASSEMENT",L"CLASSEMENT GLOBAL",L"FERMER" },
{ L"C++ Multi-Core Benchmark",L"Sprache:",L"Vergleichen:",L"Schrift:",L"Starten",L"Bereit.",L"MULTI-CORE Tests...",L"SINGLE-CORE Tests...",L"ERGEBNIS",L"Kerne: ",L"Test",L"Ihr PC",L"Anderer PC",L"Diff",L"Pkt",L"PC waehlen...",L"Bitte zuerst starten.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> GESAMT <<",L"*** IHR PC IST SCHNELLER (+",L"*** IHR PC IST LANGSAMER (",L"*** UNENTSCHIEDEN ***",L"*** PC AUSWAEHLEN ***",L"Fehler",L"Benchmark-Fehler.",L"Unbekannter Fehler.",L"Fehler.",L"Warten",L"Warten bis fertig.",L"CPU A:",L"CPU B:",L"\x26A1 ZUSAMMENFASSUNG",L"\x26A1 ERGEBNIS ANZEIGEN",L"VS",L"IST SCHNELLER",L"SCHLIESSEN",L"MULTI-CORE",L"SINGLE-CORE",L"PKT",L"Gewonnen:",L"Tests",L"\x2605 RANGLISTE",L"GLOBALE RANGLISTE",L"SCHLIESSEN" },
{ L"Benchmark C++ Multi-Core",L"Lingua:",L"Confronta:",L"Font:",L"Avvia",L"Pronto.",L"Test MULTI-CORE...",L"Test SINGLE-CORE...",L"PUNTEGGIO FINALE",L"Core: ",L"Test",L"Tuo PC",L"Altro PC",L"Diff",L"Pts",L"Seleziona un PC...",L"Esegui prima il test.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTALE <<",L"*** IL TUO PC E PIU VELOCE (+",L"*** IL TUO PC E PIU LENTO (",L"*** PAREGGIO ***",L"*** SELEZIONA UN PC ***",L"Errore",L"Errore benchmark.",L"Errore sconosciuto.",L"Errore.",L"Attendi",L"Attendi la fine.",L"CPU A:",L"CPU B:",L"\x26A1 RIEPILOGO",L"\x26A1 VEDI RISULTATO",L"VS",L"E PIU VELOCE",L"CHIUDI",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Vinto:",L"test",L"\x2605 CLASSIFICA",L"CLASSIFICA GLOBALE",L"CHIUDI" },
{ L"C++ Multi-Core Benchmark",L"Yan Yu:",L"Bi Jiao:",L"Zi Ti:",L"Kai Shi",L"Jiu Xu",L"MULTI-CORE...",L"SINGLE-CORE...",L"ZUI ZHONG DE FEN",L"He Xin: ",L"Ce Shi",L"Ni De PC",L"Qi Ta PC",L"Cha Yi",L"Fen",L"Xuan Ze PC...",L"Qing Xian Yun Xing.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> ZONG JI <<",L"*** NI DE PC GENG KUAI (+",L"*** NI DE PC GENG MAN (",L"*** PING JU ***",L"*** XUAN ZE PC ***",L"Cuo Wu",L"Benchmark Cuo Wu.",L"Wei Zhi Cuo Wu.",L"Cuo Wu.",L"Deng Dai",L"Deng Dai Wan Cheng.",L"CPU A:",L"CPU B:",L"\x26A1 ZONG JIE",L"\x26A1 CHA KAN JIE GUO",L"VS",L"GENG KUAI",L"GUAN BI",L"MULTI-CORE",L"SINGLE-CORE",L"FEN",L"Ying:",L"ce shi",L"\x2605 PAI MING",L"QUAN QIU PAI MING",L"GUAN BI" },
{ L"C++ Multi-Core Benchmark",L"Yazyk:",L"Sravnit:",L"Shrift:",L"Start",L"Gotov.",L"MULTI-CORE...",L"SINGLE-CORE...",L"ITOG",L"Yadra: ",L"Test",L"Vash PK",L"Drugoy PK",L"Razn",L"Pts",L"Vyberite PK...",L"Snachala zapustite.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> ITOGO <<",L"*** VASH PK BYSTREE (+",L"*** VASH PK MEDLENNEE (",L"*** NICHYA ***",L"*** VYBERITE PK ***",L"Oshibka",L"Oshibka testa.",L"Neizvestnaya oshibka.",L"Oshibka.",L"Zhdite",L"Zhdite okonchaniya.",L"CPU A:",L"CPU B:",L"\x26A1 ITog",L"\x26A1 SMOTRET REZULTAT",L"VS",L"BYSTREE",L"ZAKRYT",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Vyigral:",L"testov",L"\x2605 REITING",L"GLOBALNIY REITING",L"ZAKRYT" },
{ L"C++ Multi-Core Benchmark",L"Eon Eo:",L"Bi Gyo:",L"Geul Ggol:",L"Si Jak",L"Jun Bi",L"MULTI-CORE...",L"SINGLE-CORE...",L"CHOE JONG JEOM SU",L"Ko Eo: ",L"Te Seuteu",L"Nae PC",L"Da Reun PC",L"Cha I",L"Jeom",L"PC Seon Taek...",L"Meon Jeo Sil Haeng.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> HAB GYE <<",L"*** NAE PC GA DEO PPA REUM (+",L"*** NAE PC GA DEO NEU RIM (",L"*** MU SEUNG BU ***",L"*** PC SEON TAEK ***",L"O Ryu",L"Benchmark O Ryu.",L"Al Su Eom Neun O Ryu.",L"O Ryu.",L"Gi Da Rim",L"Gi Da Ryeo Ju Se Yo.",L"CPU A:",L"CPU B:",L"\x26A1 YO YAK",L"\x26A1 GYEOL GWA BO GI",L"VS",L"DEO PPA REUM",L"DA GT GI",L"MULTI-CORE",L"SINGLE-CORE",L"JEOM",L"I gim:",L"te seuteu",L"\x2605 SUN WI",L"JEON CHE SUN WI",L"DA GT GI" },
{ L"C++ Multi-Core Benchmark",L"Taal:",L"Vergelijk:",L"Lettertype:",L"Start",L"Klaar.",L"MULTI-CORE...",L"SINGLE-CORE...",L"RESULTAAT",L"Kernen: ",L"Test",L"Jouw PC",L"Andere PC",L"Verschil",L"Score",L"Selecteer PC...",L"Voer eerst uit.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAAL <<",L"*** JOUW PC IS SNELLER (+",L"*** JOUW PC IS LANGZAMER (",L"*** GELIJKSPEL ***",L"*** SELECTEER PC ***",L"Fout",L"Benchmark fout.",L"Onbekende fout.",L"Fout.",L"Wacht",L"Wacht tot voltooid.",L"CPU A:",L"CPU B:",L"\x26A1 SAMENVATTING",L"\x26A1 BEKIJK RESULTAAT",L"VS",L"IS SNELLER",L"SLUITEN",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gewonnen:",L"tests",L"\x2605 RANGSCHIKKING",L"GLOBALE RANGSCHIKKING",L"SLUITEN" },
{ L"Benchmark C++ Multi-Core",L"Jezyk:",L"Porownaj:",L"Czcionka:",L"Start",L"Gotowy.",L"MULTI-CORE...",L"SINGLE-CORE...",L"WYNIK",L"Rdzenie: ",L"Test",L"Twoj PC",L"Inny PC",L"Roznica",L"Wynik",L"Wybierz PC...",L"Najpierw uruchom.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> RAZEM <<",L"*** TWOJ PC SZYBSZY (+",L"*** TWOJ PC WOLNIEJSZY (",L"*** REMIS ***",L"*** WYBIERZ PC ***",L"Blad",L"Blad testu.",L"Nieznany blad.",L"Blad.",L"Czekaj",L"Czekaj na koniec.",L"CPU A:",L"CPU B:",L"\x26A1 PODSUMOWANIE",L"\x26A1 ZOBACZ WYNIK",L"VS",L"SZYBSZY",L"ZAMKNIJ",L"MULTI-CORE",L"SINGLE-CORE",L"PKT",L"Wygrane:",L"testy",L"\x2605 RANKING",L"RANKING GLOBALNY",L"ZAMKNIJ" },
{ L"C++ Multi-Core Benchmark",L"Nihongo:",L"Hikaku:",L"Font:",L"Kaishi",L"Junbi",L"MULTI-CORE...",L"SINGLE-CORE...",L"SAISHUU SUKOA",L"Koa: ",L"Tesuto",L"Anata PC",L"Hoka PC",L"Sai",L"Sukoa",L"PC Sentaku...",L"Saisho Ni Jikkou.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> GOUKEI <<",L"*** ANATA PC HAYAI (+",L"*** ANATA PC OSOI (",L"*** HIKIWAKE ***",L"*** PC SENTAKU ***",L"Era",L"Benchmark Era.",L"Fumei Era.",L"Era.",L"Machi",L"Shuuryou Wo Machi.",L"CPU A:",L"CPU B:",L"\x26A1 MATOME",L"\x26A1 KEKKA WO MIRU",L"VS",L"HAYAI",L"ToJiRu",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Kachi:",L"tesuto",L"\x2605 RANKINGU",L"SEKAI RANKINGU",L"ToJiRu" }
};

HWND hEditLog=NULL,hBtnRun=NULL,hComboLang=NULL,hComboCompare=NULL,hComboFont=NULL;
HWND hStaticLang=NULL,hStaticCompare=NULL,hStaticStatus=NULL,hStaticFont=NULL,hMainWnd=NULL;
HWND hStaticCpuA=NULL,hComboCpuA=NULL,hStaticCpuB=NULL,hComboCpuB=NULL;
HWND hBtnResumo=NULL,hBtnVerResultado=NULL,hBtnRanking=NULL;
HWND hModalWnd=NULL,hRankingWnd=NULL;

HFONT hFontAtual=NULL;
HFONT hFontModalTitulo=NULL,hFontModalPct=NULL,hFontModalNome=NULL;
HFONT hFontModalMsg=NULL,hFontModalPts=NULL,hFontModalCard=NULL;
HFONT hFontModalBtn=NULL,hFontModalVs=NULL;
HFONT hFontRankTitulo=NULL,hFontRankHeader=NULL,hFontRankNome=NULL;
HFONT hFontRankPts=NULL,hFontRankBtn=NULL,hFontRankNum=NULL;

int currentFontSize=21,currentLangIndex=0,g_winW=1450,g_winH=910;

std::wstring g_cabecalhoAtual=L"";
bool g_modoCpuXCpuAtivo=false;
int g_modalIdxA=-1,g_modalIdxB=-1;
bool g_modalMeuPcVsOutro=false;
int g_rankScrollMulti=0,g_rankScrollSingle=0;
int g_linhaDestacada=-1;
bool g_trackingMouse=false;
WNDPROC g_oldEditLogProc=NULL;

struct PCReferencia {
std::wstring nome;
double scoresMultiCore[100];
double scoresSingleCore[100];
double totalMultiCore;
double totalSingleCore;
int numThreads;
};

std::vector<PCReferencia> pcsCadastrados = {
{ L"Selecione um PC para comparar...",{0},{0},0.0,0.0,0 }
};

double meuUltimoScoreTestsMulti[100]={0};
double meuUltimoScoreTestsSingle[100]={0};
double meuUltimoTotalMulti=0,meuUltimoTotalSingle=0;
int meuUltimoNumThreads=0;
bool benchmarkRealizado=false,benchmarkEmAndamento=false;

void AtualizarFontesSimples(int fontSize);
void AtualizarIdiomaInterface(int langIndex);
void AtualizarPainelComparativo();
void AtualizarListaComparacao();
void PosicionarControlesTopo();
void AtualizarPainelPrincipal();
void AbrirModalResumo(int idxA,int idxB,bool meuPcVsOutro);
void FecharModal();
void VerificarBotoesResumo();
void DesenharPainelModal(HDC hdc,RECT& area,bool isMulti,int idxA,int idxB,bool meuPcVsOutro);
LRESULT CALLBACK ModalProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void AbrirRanking();
void FecharRanking();
void DesenharRanking(HDC hdc,RECT& rc);
LRESULT CALLBACK RankingProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK EditLogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
int MedirTextoLargura(HFONT fonte,const wchar_t* texto);
void ObterSelecaoCpuXCpu(int&idxA,int&idxB);
void CriarFontesRanking();
void DestruirFontesRanking();
void CriarFontesModal();
void DestruirFontesModal();

std::wstring Utf8ToWstring(const std::string& str){if(str.empty())return L"";int s=MultiByteToWideChar(CP_UTF8,0,&str[0],(int)str.size(),NULL,0);std::wstring w(s,0);MultiByteToWideChar(CP_UTF8,0,&str[0],(int)str.size(),&w[0],s);return w;}
std::string WstringToUtf8(const std::wstring& wstr){if(wstr.empty())return"";int s=WideCharToMultiByte(CP_UTF8,0,&wstr[0],(int)wstr.size(),NULL,0,NULL,NULL);std::string str(s,0);WideCharToMultiByte(CP_UTF8,0,&wstr[0],(int)wstr.size(),&str[0],s,NULL,NULL);return str;}

std::wstring ObterNomeCompletoCPU(){HKEY hKey;wchar_t buffer[256]=L"CPU Desconhecido";DWORD bs=sizeof(buffer);if(RegOpenKeyExW(HKEY_LOCAL_MACHINE,L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",0,KEY_READ,&hKey)==ERROR_SUCCESS){RegQueryValueExW(hKey,L"ProcessorNameString",NULL,NULL,(LPBYTE)buffer,&bs);RegCloseKey(hKey);}std::wstring nome(buffer);size_t lc=nome.find_last_not_of(L"\r\n\t ");if(lc!=std::wstring::npos)nome.erase(lc+1);return nome;}

// Correcao: declaracoes antecipadas para total convertido
double ScoreParaExibicao(int i,double valor);
double TotalParaExibicao(const double scores[100]);
double TotalParaExibicaoVector(const std::vector<double>& scores);

// === JSON BLINDADO ===
std::string GerarJsonCompleto(){std::string json="{\"data\":[";bool p=true;for(size_t i=1;i<pcsCadastrados.size();++i){if(!p)json+=",";p=false;std::wstring ne=pcsCadastrados[i].nome;size_t pos=0;while((pos=ne.find(L'"',pos))!=std::wstring::npos){ne.replace(pos,1,L"\\\"");pos+=2;}json+="{\"nome\":\""+WstringToUtf8(ne)+"\",\"totalMulti\":"+std::to_string(TotalParaExibicao(pcsCadastrados[i].scoresMultiCore))+",\"totalSingle\":"+std::to_string(TotalParaExibicao(pcsCadastrados[i].scoresSingleCore))+",\"threads\":"+std::to_string(pcsCadastrados[i].numThreads)+",\"scoresMulti\":[";for(int j=0;j<100;++j){json+=std::to_string(pcsCadastrados[i].scoresMultiCore[j]);if(j<99)json+=",";}json+="],\"scoresSingle\":[";for(int j=0;j<100;++j){json+=std::to_string(pcsCadastrados[i].scoresSingleCore[j]);if(j<99)json+=",";}json+="]}";}json+="]}";return json;}

std::string BaixarJsonNuvem(){std::string r;HINTERNET hI=InternetOpenW(L"BenchmarkAppClient",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);if(!hI)return"";std::wstring url=GetNpointUrl();HINTERNET hF=InternetOpenUrlW(hI,url.c_str(),NULL,0,INTERNET_FLAG_RELOAD|INTERNET_FLAG_SECURE|INTERNET_FLAG_NO_CACHE_WRITE,0);if(hF){char buf[8192];DWORD br=0;while(InternetReadFile(hF,buf,sizeof(buf)-1,&br)&&br>0){buf[br]='\0';r+=buf;}InternetCloseHandle(hF);}InternetCloseHandle(hI);return r;}

std::vector<double> ExtrairArrayDouble(const std::string& json,size_t sp){std::vector<double> r;size_t p=json.find('[',sp);if(p==std::string::npos)return r;p++;while(p<json.size()){while(p<json.size()&&(json[p]==' '||json[p]=='\t'||json[p]=='\n'||json[p]=='\r'))p++;if(p>=json.size()||json[p]==']')break;size_t ns=p;while(p<json.size()&&json[p]!=','&&json[p]!=']')p++;if(p>ns){try{r.push_back(std::stod(json.substr(ns,p-ns)));}catch(...){}}if(p<json.size()&&json[p]==',')p++;}return r;}

void MesclarDadosNaMemoria(const std::string& jn){size_t pa=jn.find("\"data\":[");if(pa==std::string::npos)return;size_t p=pa+7;while((p=jn.find("{\"nome\"",p))!=std::string::npos){size_t eo=jn.find("}",p);if(eo==std::string::npos)break;size_t sn=jn.find(":\"",p)+2,en=jn.find("\"",sn);if(sn==std::string::npos||en==std::string::npos||en>eo){p++;continue;}std::wstring wn=Utf8ToWstring(jn.substr(sn,en-sn));double tm=0,ts=0;int th=0;size_t ptm=jn.find("\"totalMulti\":",en);if(ptm!=std::string::npos&&ptm<eo)try{tm=std::stod(jn.substr(ptm+13));}catch(...){}size_t pts2=jn.find("\"totalSingle\":",en);if(pts2!=std::string::npos&&pts2<eo)try{ts=std::stod(jn.substr(pts2+14));}catch(...){}size_t pth=jn.find("\"threads\":",en);if(pth!=std::string::npos&&pth<eo)try{th=std::stoi(jn.substr(pth+10));}catch(...){}auto smv=ExtrairArrayDouble(jn,en);size_t pefa=jn.find(']',en);std::vector<double> ssv;if(pefa!=std::string::npos&&pefa<eo)ssv=ExtrairArrayDouble(jn,pefa);bool ex=false;for(size_t k=1;k<pcsCadastrados.size();++k){if(pcsCadastrados[k].nome==wn){ex=true;bool at=false;double novoMultiVis=TotalParaExibicaoVector(smv);
double atualMultiVis=TotalParaExibicao(pcsCadastrados[k].scoresMultiCore);
if(!smv.empty()&&novoMultiVis>atualMultiVis){pcsCadastrados[k].totalMultiCore=novoMultiVis;for(int s=0;s<100&&s<(int)smv.size();++s)pcsCadastrados[k].scoresMultiCore[s]=smv[s];at=true;}double novoSingleVis=TotalParaExibicaoVector(ssv);
double atualSingleVis=TotalParaExibicao(pcsCadastrados[k].scoresSingleCore);
if(!ssv.empty()&&novoSingleVis>atualSingleVis){pcsCadastrados[k].totalSingleCore=novoSingleVis;for(int s=0;s<100&&s<(int)ssv.size();++s)pcsCadastrados[k].scoresSingleCore[s]=ssv[s];at=true;}if(at&&th>0)pcsCadastrados[k].numThreads=th;break;}}if(!ex){PCReferencia nv;nv.nome=wn;nv.totalMultiCore=TotalParaExibicaoVector(smv);nv.totalSingleCore=TotalParaExibicaoVector(ssv);nv.numThreads=th;for(int s=0;s<100;++s){nv.scoresMultiCore[s]=(s<(int)smv.size())?smv[s]:0.0;nv.scoresSingleCore[s]=(s<(int)ssv.size())?ssv[s]:0.0;}pcsCadastrados.push_back(nv);}p=eo+1;}}

void CarregarListaNuvem(HWND hwnd){std::string jn=BaixarJsonNuvem();if(!jn.empty()&&jn.find("\"data\"")!=std::string::npos)MesclarDadosNaMemoria(jn);}

bool SalvarListaNuvemNativo(){std::string jan=BaixarJsonNuvem();if(jan.empty()||jan.find("\"data\"")==std::string::npos)return false;MesclarDadosNaMemoria(jan);std::string jd=GerarJsonCompleto();if(jd=="{\"data\":[]}"||jd.length()<20)return false;HINTERNET hs=InternetOpenW(L"BenchmarkClient",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);if(!hs)return false;HINTERNET hc=InternetConnectW(hs,L"api.npoint.io",INTERNET_DEFAULT_HTTPS_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);if(!hc){InternetCloseHandle(hs);return false;}std::wstring path=GetNpointPath();HINTERNET hr=HttpOpenRequestW(hc,L"POST",path.c_str(),NULL,NULL,NULL,INTERNET_FLAG_SECURE|INTERNET_FLAG_RELOAD,0);if(!hr){InternetCloseHandle(hc);InternetCloseHandle(hs);return false;}std::wstring hdrs=L"Content-Type: application/json\r\nAccept: */*\r\n";BOOL ev=HttpSendRequestW(hr,hdrs.c_str(),(DWORD)hdrs.size(),(LPVOID)jd.c_str(),(DWORD)jd.size());InternetCloseHandle(hr);InternetCloseHandle(hc);InternetCloseHandle(hs);return ev==TRUE;}

double calcularScoreNormalizado(long long tOps,double tSeg,double fEsc){if(tSeg<=0)return 0;return((double)tOps/tSeg/fEsc)/100.0;}

// =============================================================================
// HELPERS: LOG10, FORMATACAO, VERMELHO, HOVER
// =============================================================================
static const int g_testesLog10x100[] = {
    0, 5, 7, 8, 11, 15, 19, 21, 25, 32,
    34, 35, 36, 37, 39, 40, 41, 42, 43, 44,
    45, 47, 48, 49, 50, 56, 60, 62, 63, 64,
    66, 68, 71, 72, 73, 74, 79, 80, 82, 83
};

bool TesteUsaLog10x100(int i){for(int x:g_testesLog10x100){if(x==i)return true;}return false;}

double ScoreParaExibicao(int i,double valor){
if(i==81){if(valor<=0.0||valor!=valor)return 0.0;return std::log10(valor)*200.0;}
    if(!TesteUsaLog10x100(i))return valor;
    if(valor<=0.0||valor!=valor)return 0.0;
    return std::log10(valor)*150.0;
}

double TotalParaExibicao(const double scores[100]){
    double total=0.0;
    for(int i=0;i<100;++i)total+=ScoreParaExibicao(i,scores[i]);
    return total;
}

double TotalParaExibicaoVector(const std::vector<double>& scores){
double total=0.0;
for(int i=0;i<100;++i){
double v=(i<(int)scores.size())?scores[i]:0.0;
total+=ScoreParaExibicao(i,v);
}
return total;
}

std::wstring FormatarNumero2Decimais(double valor){
    if(valor!=valor)valor=0.0;
    bool neg=valor<0.0;
    if(neg)valor=-valor;
    if(valor>9000000000000000.0)valor=9000000000000000.0;
    long long cents=(long long)(valor*100.0+0.5);
    if(cents==0)neg=false;
    long long inteiro=cents/100;
    int dec=(int)(cents%100);
    std::wstring s=std::to_wstring(inteiro);
    int pos=(int)s.size()-3;
    while(pos>0){s.insert(pos,L".");pos-=3;}
    wchar_t d[4];swprintf_s(d,L"%02d",dec);
    std::wstring r=s+L","+d;
    if(neg)r=L"-"+r;
    return r;
}

std::wstring FormatarPontosFinal(double valor){
    if(valor!=valor)valor=0.0;
    if(valor<0.0)valor=0.0;
    if(valor>9000000000000000.0)valor=9000000000000000.0;
    long long v=(long long)(valor+0.5);
    std::wstring s=std::to_wstring(v);
    int pos=(int)s.size()-3;
    while(pos>0){s.insert(pos,L".");pos-=3;}
    return s;
}

double ConverterNumeroTexto(std::wstring t){
    t.erase(std::remove(t.begin(),t.end(),L'.'),t.end());
    t.erase(std::remove(t.begin(),t.end(),L' '),t.end());
    for(size_t i=0;i<t.size();++i){if(t[i]==L',')t[i]=L'.';}
    std::string utf=WstringToUtf8(t);
    if(utf.empty())return 0.0;
    try{return std::stod(utf);}catch(...){return 0.0;}
}

std::wstring ObterTextoDaLinha(HWND hwnd,int linha){
    if(!hwnd)return L"";
    LONG inicio=(LONG)SendMessageW(hwnd,EM_LINEINDEX,linha,0);
    LONG len=(LONG)SendMessageW(hwnd,EM_LINELENGTH,inicio,0);
    if(len<=0)return L"";
    std::wstring linhaTxt(len,L'\0');
    *((WORD*)&linhaTxt[0])=(WORD)len;
    int copiado=(int)SendMessageW(hwnd,EM_GETLINE,linha,(LPARAM)&linhaTxt[0]);
    linhaTxt.resize(copiado);
    return linhaTxt;
}

bool LinhaEhDadoComparacao(const std::wstring& linha){
    if(linha.empty())return false;
    return linha[0]>=L'0'&&linha[0]<=L'9';
}

void AplicarLinhaTotalMaior(int linha){
    if(!hEditLog)return;
    LONG inicio=(LONG)SendMessageW(hEditLog,EM_LINEINDEX,linha,0);
    LONG len=(LONG)SendMessageW(hEditLog,EM_LINELENGTH,inicio,0);
    if(len<=0)return;
    SendMessageW(hEditLog,EM_SETSEL,inicio,inicio+len);
    CHARFORMAT2W cf={0};cf.cbSize=sizeof(cf);
    cf.dwMask=CFM_SIZE|CFM_BOLD|CFM_COLOR;
    cf.yHeight=currentFontSize*10;
    cf.dwEffects=CFE_BOLD;
    cf.crTextColor=RGB(0,0,0);
    SendMessageW(hEditLog,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);
}

void PintarLinhaEdit(HWND hwnd,int linha,COLORREF cor){
    if(!hwnd)return;
    int total=(int)SendMessageW(hwnd,EM_GETLINECOUNT,0,0);
    if(linha<0||linha>=total)return;
    LONG inicio=(LONG)SendMessageW(hwnd,EM_LINEINDEX,linha,0);
    LONG len=(LONG)SendMessageW(hwnd,EM_LINELENGTH,inicio,0);
    if(len<=0)return;
    POINT sp={0,0};SendMessageW(hwnd,EM_GETSCROLLPOS,0,(LPARAM)&sp);
    DWORD selS=0,selE=0;SendMessageW(hwnd,EM_GETSEL,(WPARAM)&selS,(LPARAM)&selE);
    SendMessageW(hwnd,WM_SETREDRAW,FALSE,0);
    SendMessageW(hwnd,EM_SETREADONLY,FALSE,0);
    SendMessageW(hwnd,EM_SETSEL,inicio,inicio+len);
    CHARFORMAT2W cf={0};cf.cbSize=sizeof(cf);
    cf.dwMask=CFM_BACKCOLOR;cf.crBackColor=cor;
    SendMessageW(hwnd,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);
    SendMessageW(hwnd,EM_SETREADONLY,TRUE,0);
    SendMessageW(hwnd,EM_SETSEL,selS,selE);
    SendMessageW(hwnd,EM_SETSCROLLPOS,0,(LPARAM)&sp);
    SendMessageW(hwnd,WM_SETREDRAW,TRUE,0);
    InvalidateRect(hwnd,NULL,TRUE);
}

void FormatarLogComparacao(){
    if(!hEditLog)return;
    int totalLinhas=(int)SendMessageW(hEditLog,EM_GETLINECOUNT,0,0);
    POINT sp={0,0};SendMessageW(hEditLog,EM_GETSCROLLPOS,0,(LPARAM)&sp);
    DWORD selS=0,selE=0;SendMessageW(hEditLog,EM_GETSEL,(WPARAM)&selS,(LPARAM)&selE);
    SendMessageW(hEditLog,WM_SETREDRAW,FALSE,0);
    SendMessageW(hEditLog,EM_SETREADONLY,FALSE,0);
    CHARFORMAT2W cf={0};cf.cbSize=sizeof(cf);
    cf.dwMask=CFM_COLOR;cf.crTextColor=RGB(255,0,0);
    std::wstring totalTxt=traducoes[currentLangIndex].compTotal;
    for(int li=0;li<totalLinhas;++li){
        std::wstring linha=ObterTextoDaLinha(hEditLog,li);
        if(linha.empty())continue;
        if(linha.find(totalTxt)!=std::wstring::npos){AplicarLinhaTotalMaior(li);continue;}
        if(!LinhaEhDadoComparacao(linha))continue;
        size_t p1=linha.find(L'|');if(p1==std::wstring::npos)continue;
        size_t p2=linha.find(L'|',p1+1);if(p2==std::wstring::npos)continue;
        size_t p3=linha.find(L'|',p2+1);if(p3==std::wstring::npos)continue;
        size_t iniA=linha.find_first_not_of(L" \t",p1+1);
        size_t fimA=linha.find_last_not_of(L" \t",p2-1);
        size_t iniB=linha.find_first_not_of(L" \t",p2+1);
        size_t fimB=linha.find_last_not_of(L" \t",p3-1);
        if(iniA==std::wstring::npos||fimA==std::wstring::npos||iniB==std::wstring::npos||fimB==std::wstring::npos||fimA<iniA||fimB<iniB)continue;
        std::wstring sa=linha.substr(iniA,fimA-iniA+1);
        std::wstring sb=linha.substr(iniB,fimB-iniB+1);
        double va=ConverterNumeroTexto(sa);
        double vb=ConverterNumeroTexto(sb);
        LONG inicio=(LONG)SendMessageW(hEditLog,EM_LINEINDEX,li,0);
        if(va<vb){SendMessageW(hEditLog,EM_SETSEL,inicio+(LONG)iniA,inicio+(LONG)fimA+1);SendMessageW(hEditLog,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);}
        else if(vb<va){SendMessageW(hEditLog,EM_SETSEL,inicio+(LONG)iniB,inicio+(LONG)fimB+1);SendMessageW(hEditLog,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);}
    }
    SendMessageW(hEditLog,EM_SETREADONLY,TRUE,0);
    SendMessageW(hEditLog,EM_SETSEL,selS,selE);
    SendMessageW(hEditLog,EM_SETSCROLLPOS,0,(LPARAM)&sp);
    SendMessageW(hEditLog,WM_SETREDRAW,TRUE,0);
    InvalidateRect(hEditLog,NULL,TRUE);
}

LRESULT CALLBACK EditLogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    if(msg==WM_MOUSEMOVE){
        if(benchmarkEmAndamento)return CallWindowProcW(g_oldEditLogProc,hwnd,msg,wParam,lParam);
        int x=(short)LOWORD(lParam);int y=(short)HIWORD(lParam);
        POINT pt={x,y};
        LONG ch=(LONG)SendMessageW(hwnd,EM_CHARFROMPOS,0,(LPARAM)&pt);
        if(ch>=0){
            int li=(int)SendMessageW(hwnd,EM_LINEFROMCHAR,ch,0);
            std::wstring txt=ObterTextoDaLinha(hwnd,li);
            if(LinhaEhDadoComparacao(txt)){
                if(!g_trackingMouse){TRACKMOUSEEVENT tme;tme.cbSize=sizeof(tme);tme.dwFlags=TME_LEAVE;tme.hwndTrack=hwnd;tme.dwHoverTime=0;TrackMouseEvent(&tme);g_trackingMouse=true;}
                if(li!=g_linhaDestacada){
                    if(g_linhaDestacada>=0)PintarLinhaEdit(hwnd,g_linhaDestacada,RGB(255,255,255));
                    PintarLinhaEdit(hwnd,li,RGB(255,255,170));
                    g_linhaDestacada=li;
                }
            }else{
                if(g_linhaDestacada>=0){PintarLinhaEdit(hwnd,g_linhaDestacada,RGB(255,255,255));g_linhaDestacada=-1;}
            }
        }
    }else if(msg==WM_MOUSELEAVE){
        if(g_linhaDestacada>=0){PintarLinhaEdit(hwnd,g_linhaDestacada,RGB(255,255,255));g_linhaDestacada=-1;}
        g_trackingMouse=false;
    }
    if(g_oldEditLogProc)return CallWindowProcW(g_oldEditLogProc,hwnd,msg,wParam,lParam);
    return DefWindowProcW(hwnd,msg,wParam,lParam);
}

#include <numeric>
#include <cstring>

// === 100 BENCHMARKS ===

long long benchmarkPontoFlutuante(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double r=0;while(true){for(int i=1;i<=1000;++i)r+=std::sin(i)*std::cos(i)+std::sqrt(i);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMatrizInteiros(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int n=128;std::vector<int>a(n*n,3),b(n*n,5),r(n*n,0);while(true){for(int i=0;i<n;++i)for(int j=0;j<n;++j){int s=0;for(int k=0;k<n;++k)s+=a[i*n+k]*b[k*n+j];r[i*n+j]=s;}c+=n*n;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkOrdenacao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1337);std::vector<int>v(10000);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100000;});std::sort(v.begin(),v.end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPrimos(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0,n=500000;while(true){bool p=true;for(long long i=2;i<=std::sqrt((double)n);++i)if(n%i==0){p=false;break;}c++;n++;if(n>900000)n=500000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAlocacaoMemoria(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){{std::vector<double>b(2048,3.14);volatile double v=b[1024];(void)v;}c+=2048;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBitwise(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;unsigned int v=0x12345678;while(true){for(int i=0;i<1000;++i){v^=(v<<13);v^=(v>>17);v^=(v<<5);}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHashSimulado(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;unsigned long long h=5381;char txt[]="BenchmarkMassivoMultiThread";while(true){for(int i=0;i<(int)sizeof(txt)-1;++i)h=((h<<5)+h)+txt[i];c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCacheStress(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int n=65536;std::vector<int>b(n,1);while(true){for(int i=0;i<n;i+=7)b[(i*31)%n]+=i;c+=n;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPolinomios(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double x=1.0001;while(true){for(int i=0;i<500;++i){x=x*x+2.0*x+1.0;if(x>1e10)x=1.0001;}c+=500;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLogicaArray(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<bool>f(2048,false);while(true){for(size_t i=0;i<f.size();++i){f[i]=!f[i];if(i>0)f[i]=f[i]^f[i-1];}c+=f.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCriptografia(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;uint32_t h0=0x6a09e667,h1=0xbb67ae85,h2=0x3c6ef372,h3=0xa54ff53a;while(true){for(int i=0;i<100;++i){uint32_t s0=(h0>>2|h0<<30)^(h0>>13|h0<<19)^(h0>>22|h0<<10);uint32_t s1=(h1>>6|h1<<26)^(h1>>11|h1<<21)^(h1>>25|h1<<7);h3=h2;h2=h1;h1=h0;h0=s0+s1+h3+i;}c+=100;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCompressao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<char>data(1024,'A');while(true){int cnt=1;for(size_t i=1;i<data.size();++i){if(data[i]==data[i-1])cnt++;else cnt=1;}c+=data.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFisica(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct Body{double x,y,vx,vy;};std::vector<Body>bodies(50);for(auto&b:bodies){b.x=rand()%100;b.y=rand()%100;b.vx=1;b.vy=1;}while(true){for(auto&b:bodies){b.x+=b.vx;b.y+=b.vy;if(b.x>100||b.x<0)b.vx*=-1;if(b.y>100||b.y<0)b.vy*=-1;}c+=bodies.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkGameOfLife(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int w=100,h=100;std::vector<std::vector<bool>>g(w,std::vector<bool>(h,false)),n(w,std::vector<bool>(h,false));std::mt19937 rng(42);for(int x=0;x<w;++x)for(int y=0;y<h;++y)g[x][y]=(rng()%2==0);while(true){for(int x=1;x<w-1;++x)for(int y=1;y<h-1;++y){int nb=0;for(int dx=-1;dx<=1;++dx)for(int dy=-1;dy<=1;++dy){if(dx==0&&dy==0)continue;if(g[x+dx][y+dy])nb++;}if(g[x][y])n[x][y]=(nb==2||nb==3);else n[x][y]=(nb==3);}std::swap(g,n);c+=w*h;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAudio(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double p=0;while(true){for(int i=0;i<4410;++i){p+=440.0/44100.0;if(p>1.0)p-=1.0;volatile double s=std::sin(p*2.0*3.14159);}c+=4410;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRede(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>pkt(1500,0xFF);while(true){uint32_t cs=0;for(size_t i=0;i<pkt.size();i+=2)cs+=(pkt[i]<<8)|pkt[i+1];c+=pkt.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkIA(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double w[10]={0.5},in[10]={1.0};while(true){double s=0;for(int i=0;i<10;++i)s+=w[i]*in[i];double o=1.0/(1.0+std::exp(-s));for(int i=0;i<10;++i)w[i]+=0.001*o;c+=10;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDatabase(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>idx(10000);std::iota(idx.begin(),idx.end(),0);while(true){int tgt=rand()%10000;bool f=std::binary_search(idx.begin(),idx.end(),tgt);c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkParticulas(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct P{float x,y,l;};std::vector<P>ps(1000);while(true){for(auto&p:ps){p.x+=0.1f;p.y+=0.1f;p.l-=0.01f;if(p.l<=0){p.l=1.0f;p.x=0;p.y=0;}}c+=ps.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSteganografia(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>img(4096,128),sec(512,1);while(true){for(size_t i=0;i<sec.size();++i)img[i]=(img[i]&0xFE)|(sec[i]&1);c+=sec.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMandelbrot(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int y=-100;y<=100;++y)for(int x=-100;x<=100;++x){double zx=0,zy=0,cx=x/50.0,cy=y/50.0;int i=0;for(;i<100&&(zx*zx+zy*zy)<4.0;++i){double tmp=zx*zx-zy*zy+cx;zy=2.0*zx*zy+cy;zx=tmp;}c+=i;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFourier(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>sig(1024,0);std::mt19937 rng(99);for(auto&s:sig)s=(rng()%1000)/1000.0;while(true){for(int k=0;k<1024;++k){double re=0,im=0;for(int n=0;n<1024;++n){double a=2.0*3.14159*k*n/1024;re+=sig[n]*std::cos(a);im-=sig[n]*std::sin(a);}}c+=1024*1024;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkShortestPath(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>>g(V,std::vector<int>(V,999));std::mt19937 rng(77);for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(i!=j)g[i][j]=rng()%100;while(true){std::vector<int>dist(V,999999);std::vector<bool>vis(V,false);dist[0]=0;for(int cnt=0;cnt<V-1;++cnt){int u=-1;for(int v=0;v<V;++v)if(!vis[v]&&(u==-1||dist[v]<dist[u]))u=v;if(dist[u]==999999)break;vis[u]=true;for(int v=0;v<V;++v)if(!vis[v]&&g[u][v]!=999&&dist[u]+g[u][v]<dist[v])dist[v]=dist[u]+g[u][v];}c+=V*V;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRegex(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string txt="abc123def456ghi789jkl012mno345pqr678stu901vwx234yz";while(true){for(int i=0;i<10000;++i){bool m=false;for(size_t j=0;j+2<txt.size();++j)if(std::isdigit(txt[j])&&std::isdigit(txt[j+1])&&std::isdigit(txt[j+2])){m=true;break;}if(m)c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkXML(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string xml="<root><item id='1'><name>Test</name></item></root>";while(true){size_t p=0;while((p=xml.find('<',p))!=std::string::npos){size_t e=xml.find('>',p);if(e==std::string::npos)break;p=e+1;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMultiplicacaoMatriz(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=200;std::vector<std::vector<double>>A(N,std::vector<double>(N,1.5)),B(N,std::vector<double>(N,2.0)),C(N,std::vector<double>(N,0));while(true){for(int i=0;i<N;++i)for(int j=0;j<N;++j)for(int k=0;k<N;++k)C[i][j]+=A[i][k]*B[k][j];c+=N*N*N;for(int i=0;i<N;++i)for(int j=0;j<N;++j)C[i][j]=0;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRayTracing(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct S{double x,y,z,r;};std::vector<S>sp={{0,0,5,1},{2,1,6,1.5},{-2,-1,7,1.2}};while(true){for(int py=0;py<100;++py)for(int px=0;px<100;++px){double rx=(px-50)/50.0,ry=(py-50)/50.0,rz=1.0;for(auto&s:sp){double a=rx*rx+ry*ry+rz*rz;double b=2*(rx*(-s.x)+ry*(-s.y)+rz*(-s.z));double cc=s.x*s.x+s.y*s.y+s.z*s.z-s.r*s.r;if(b*b-4*a*cc>=0)c++;}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkGenetico(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int PS=100,G=50;std::mt19937 rng(12345);std::vector<std::vector<int>>pop(PS,std::vector<int>(G));for(auto&i:pop)for(auto&g:i)g=rng()%2;while(true){for(auto&i:pop){int f=0;for(int g:i)f+=g;c++;}for(int i=0;i<PS/2;++i){int cp=rng()%G;for(int j=cp;j<G;++j)std::swap(pop[i][j],pop[PS-1-i][j]);}for(auto&i:pop)if(rng()%100<5){int p=rng()%G;i[p]=!i[p];}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFluidos(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int G=64;std::vector<std::vector<double>>den(G,std::vector<double>(G,1.0)),nd(G,std::vector<double>(G,0));while(true){for(int i=1;i<G-1;++i)for(int j=1;j<G-1;++j)nd[i][j]=(den[i][j]+den[i-1][j]+den[i+1][j]+den[i][j-1]+den[i][j+1])/5.0;std::swap(den,nd);c+=G*G;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAESSimulado(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>blk(16,0xAA),key(16,0xBB);while(true){for(int r=0;r<10;++r){for(int i=0;i<16;++i)blk[i]=(blk[i]<<3)^(blk[i]>>5)^key[i];std::rotate(blk.begin(),blk.begin()+(r%4),blk.end());for(int i=0;i<12;++i)blk[i]^=blk[i+1]^blk[i+2];for(int i=0;i<16;++i)blk[i]^=key[i];}c+=16;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAStar(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int G=50;std::mt19937 rng(54321);while(true){std::vector<std::vector<bool>>w(G,std::vector<bool>(G,true));for(int i=0;i<G*G/4;++i)w[rng()%G][rng()%G]=false;std::vector<std::vector<int>>dist(G,std::vector<int>(G,-1));std::queue<std::pair<int,int>>q;dist[0][0]=0;q.push({0,0});int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};while(!q.empty()){auto cur=q.front();q.pop();int x=cur.first,y=cur.second;c++;for(auto&dd:dirs){int nx=x+dd[0],ny=y+dd[1];if(nx>=0&&nx<G&&ny>=0&&ny<G&&w[nx][ny]&&dist[nx][ny]==-1){dist[nx][ny]=dist[x][y]+1;q.push({nx,ny});}}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMonteCarlo(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0,in=0;std::mt19937 rng(98765);std::uniform_real_distribution<double>dist(0,1);while(true){for(int i=0;i<10000;++i){double x=dist(rng),y=dist(rng);if(x*x+y*y<=1)in++;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkConvolucao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int W=128,H=128,K=3;std::vector<std::vector<double>>img(H,std::vector<double>(W,0.5)),res(H,std::vector<double>(W,0));std::vector<std::vector<double>>krn={{1,2,1},{2,4,2},{1,2,1}};while(true){for(int y=1;y<H-1;++y)for(int x=1;x<W-1;++x){double s=0;for(int ky=0;ky<K;++ky)for(int kx=0;kx<K;++kx)s+=img[y+ky-1][x+kx-1]*krn[ky][kx];res[y][x]=s/16.0;}c+=(H-2)*(W-2)*K*K;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBTree(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::map<int,int>bt;std::mt19937 rng(11111);while(true){for(int i=0;i<1000;++i){bt[rng()%100000]=rng();c++;}for(int i=0;i<500;++i){auto it=bt.find(rng()%100000);if(it!=bt.end())c++;}for(int i=0;i<100;++i){auto it=bt.find(rng()%100000);if(it!=bt.end()){bt.erase(it);c++;}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkTensor(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int D=20;std::vector<std::vector<std::vector<double>>>a(D,std::vector<std::vector<double>>(D,std::vector<double>(D,1))),b(D,std::vector<std::vector<double>>(D,std::vector<double>(D,2))),r(D,std::vector<std::vector<double>>(D,std::vector<double>(D,0)));while(true){for(int i=0;i<D;++i)for(int j=0;j<D;++j)for(int k=0;k<D;++k)r[i][j][k]=a[i][j][k]*b[i][j][k];c+=D*D*D;for(int i=0;i<D;++i)for(int j=0;j<D;++j)for(int k=0;k<D;++k)r[i][j][k]=0;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFatorial(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long r=1;for(int i=1;i<=20;++i)r*=i;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*20;}
long long benchmarkFibonacci(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long a=0,b=1;for(int i=0;i<100;++i){long long tmp=a+b;a=b;b=tmp;}c+=100;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHanoi(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;auto h=[&](auto self,int n,int f,int to,int a)->void{if(n==1){c++;return;}self(self,n-1,f,a,to);c++;self(self,n-1,a,to,f);};while(true){h(h,15,1,3,2);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCrivo(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=100000;std::vector<bool>ip(N,true);while(true){std::fill(ip.begin(),ip.end(),true);ip[0]=ip[1]=false;for(int i=2;i*i<N;++i)if(ip[i])for(int j=i*i;j<N;j+=i)ip[j]=false;c+=N;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMDC(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){for(int i=0;i<10000;++i){long long a=rng()%1000000,b=rng()%1000000;while(b){long long tmp=b;b=a%b;a=tmp;}c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPotenciaMod(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long b=2,e=100000,m=1000000007,r=1;b%=m;while(e>0){if(e%2==1)r=(r*b)%m;e>>=1;b=(b*b)%m;}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkRaizNewton(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double x=2;for(int i=0;i<1000;++i)x=0.5*(x+10.0/x);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSenoTaylor(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double x=1,term=x,sum=x;for(int n=1;n<20;++n){term*=-x*x/((2*n)*(2*n+1));sum+=term;}c+=20;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkExpMath(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double r=std::exp(1.0);(void)r;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*1000;}
long long benchmarkLogNat(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double r=std::log(2.71828);(void)r;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*1000;}
long long benchmarkAbsBulk(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>v(10000,-5.5);while(true){for(auto&x:v)x=std::abs(x);c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRoundBulk(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>v(10000,3.14159);while(true){for(auto&x:v)x=std::round(x);c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkClamp(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){for(int i=0;i<10000;++i){double v=(double)(rng()%1000);double cl=std::max(0.0,std::min(100.0,v));(void)cl;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLerp(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int i=0;i<10000;++i){double tt=(double)i/10000.0;double r=0.0+tt*(100.0-0.0);(void)r;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSpline(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(double tt=0;tt<1.0;tt+=0.01){double r=2*tt*tt*tt-3*tt*tt+1;(void)r;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBubbleSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(500);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=0;i<v.size();++i)for(size_t j=0;j+1<v.size();++j)if(v[j]>v[j+1])std::swap(v[j],v[j+1]);c+=v.size()*v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkInsertionSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(1000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=1;i<v.size();++i){int k=v[i];int j=(int)i-1;while(j>=0&&v[j]>k){v[j+1]=v[j];j--;}v[j+1]=k;}c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSelectionSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(800);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=0;i<v.size();++i){size_t mi=i;for(size_t j=i+1;j<v.size();++j)if(v[j]<v[mi])mi=j;std::swap(v[i],v[mi]);}c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkQuickSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(2000);std::mt19937 rng(1);auto qs=[&](auto self,int l,int r,std::vector<int>&a)->void{if(l<r){int p=a[l+(r-l)/2];int i=l,j=r;while(i<=j){while(a[i]<p)i++;while(a[j]>p)j--;if(i<=j){std::swap(a[i],a[j]);i++;j--;c++;}}self(self,l,j,a);self(self,i,r,a);}};while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});qs(qs,0,(int)v.size()-1,v);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMergeSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(2000);std::mt19937 rng(1);auto ms=[&](auto self,std::vector<int>&a)->void{if(a.size()<=1)return;int m=(int)a.size()/2;std::vector<int>l(a.begin(),a.begin()+m),r(a.begin()+m,a.end());self(self,l);self(self,r);size_t i=0,j=0,k=0;while(i<l.size()&&j<r.size()){if(l[i]<=r[j])a[k++]=l[i++];else a[k++]=r[j++];c++;}while(i<l.size())a[k++]=l[i++];while(j<r.size())a[k++]=r[j++];};while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});ms(ms,v);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHeapSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});std::make_heap(v.begin(),v.end());std::sort_heap(v.begin(),v.end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCountingSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(5000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100;});std::vector<int>cnt(100,0);for(int x:v)cnt[x]++;c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRadixSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100000;});int mx=*std::max_element(v.begin(),v.end());for(int exp=1;mx/exp>0;exp*=10){std::vector<int>out(v.size()),cnt(10,0);for(int i=0;i<(int)v.size();i++)cnt[(v[i]/exp)%10]++;for(int i=1;i<10;i++)cnt[i]+=cnt[i-1];for(int i=(int)v.size()-1;i>=0;i--){out[cnt[(v[i]/exp)%10]-1]=v[i];cnt[(v[i]/exp)%10]--;}for(int i=0;i<(int)v.size();i++)v[i]=out[i];c+=v.size();}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBucketSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return(double)(rng()%1000)/1000.0;});int n=(int)v.size();std::vector<std::vector<double>>bk(n);for(int i=0;i<n;i++){int bi=(int)(n*v[i]);if(bi>=n)bi=n-1;if(bi<0)bi=0;bk[bi].push_back(v[i]);}for(int i=0;i<n;i++)std::sort(bk[i].begin(),bk[i].end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkShellSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});int n=(int)v.size();for(int gap=n/2;gap>0;gap/=2)for(int i=gap;i<n;i++){int tmp=v[i];int j;for(j=i;j>=gap&&v[j-gap]>tmp;j-=gap){v[j]=v[j-gap];c++;}v[j]=tmp;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrCopy(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string src(1000,'A'),dst;while(true){dst=src;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrConcat(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s;while(true){s.clear();for(int i=0;i<100;++i)s+="ABC";c+=100;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrCmp(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s1(1000,'A'),s2(1000,'A');while(true){volatile bool r=(s1==s2);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrFind(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(10000,'A');s[5000]='B';while(true){size_t p=s.find('B');(void)p;c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrRev(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A');while(true){std::reverse(s.begin(),s.end());c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrUpper(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'a');while(true){std::transform(s.begin(),s.end(),s.begin(),::toupper);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStrTrim(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s="   Hello World   ";while(true){s.erase(0,s.find_first_not_of(' '));s.erase(s.find_last_not_of(' ')+1);c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*1000;}
long long benchmarkCSVParse(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string csv="1,2,3,4,5,6,7,8,9,10";while(true){std::stringstream ss(csv);std::string item;while(std::getline(ss,item,','))c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkJSONToken(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string json="{\"key\":\"value\",\"num\":123}";while(true){for(char ch:json)if(ch=='{'||ch=='}'||ch==':'||ch==',')c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkBase64Enc(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string in="Hello World Benchmark";while(true){std::string out;int val=0,valb=-6;for(unsigned char ch:in){val=(val<<8)+ch;valb+=8;while(valb>=0){out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);valb-=6;}}c+=in.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHexDump(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>data(1000,0xFF);while(true){std::stringstream ss;for(uint8_t b:data)ss<<std::hex<<std::setw(2)<<std::setfill('0')<<(int)b;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCRC32(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>data(1000,1);while(true){uint32_t crc=0xFFFFFFFF;for(uint8_t b:data){crc^=b;for(int i=0;i<8;i++)crc=(crc>>1)^(0xEDB88320&(-(crc&1)));}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAdler32(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>data(1000,1);while(true){uint32_t a=1,b=0;for(uint8_t dd:data){a=(a+dd)%65521;b=(b+a)%65521;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFletcher(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>data(1000,1);while(true){uint16_t s1=0,s2=0;for(uint8_t dd:data){s1=(s1+dd)%255;s2=(s2+s1)%255;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkXORCipher(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t>data(1000,1);uint8_t key=0xAA;while(true){for(auto&dd:data)dd^=key;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkROT13(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A');while(true){for(auto&ch:s)if(ch>='A'&&ch<='Z')ch='A'+(ch-'A'+13)%26;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCaesar(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A');int shift=3;while(true){for(auto&ch:s)if(ch>='A'&&ch<='Z')ch='A'+(ch-'A'+shift)%26;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVigenere(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A'),key="KEY";while(true){for(size_t i=0;i<s.size();++i){char k=key[i%key.size()];if(s[i]>='A'&&s[i]<='Z')s[i]='A'+(s[i]-'A'+k-'A')%26;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRandomFill(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(10000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng();});c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMemSet(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(10000);while(true){memset(v.data(),0,v.size()*sizeof(int));c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMemMove(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int>v(10000,1),dst(10000);while(true){memcpy(dst.data(),v.data(),v.size()*sizeof(int));c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecAdd(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>a(10000,1),b(10000,2),r(10000);while(true){for(size_t i=0;i<a.size();++i)r[i]=a[i]+b[i];c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecDot(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double>a(10000,1),b(10000,2);while(true){double r=0;for(size_t i=0;i<a.size();++i)r+=a[i]*b[i];c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecCross(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int i=0;i<10000;++i){double ax=1,ay=2,az=3,bx=4,by=5,bz=6;double cx=ay*bz-az*by,cy=az*bx-ax*bz,cz=ax*by-ay*bx;(void)cx;(void)cy;(void)cz;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMatDet(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=10;std::vector<std::vector<double>>m(N,std::vector<double>(N,1.5));while(true){double det=1;for(int i=0;i<N;++i){for(int j=i+1;j<N;++j){double f=m[j][i]/m[i][i];for(int k=i;k<N;++k)m[j][k]-=f*m[i][k];}det*=m[i][i];}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkMatInv(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=5;std::vector<std::vector<double>>m(N,std::vector<double>(N,0));for(int i=0;i<N;++i)m[i][i]=1;while(true){double det=1;for(int i=0;i<N;++i){for(int j=i+1;j<N;++j){double f=m[j][i]/m[i][i];for(int k=i;k<N;++k)m[j][k]-=f*m[i][k];}det*=m[i][i];}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkLLTraverse(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct Node{int val;Node*next;};Node*head=nullptr;for(int i=0;i<1000;++i){Node*n=new Node{i,head};head=n;}while(true){Node*cur=head;while(cur){c++;cur=cur->next;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBST(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::set<int>bst;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)bst.insert(rng()%100000);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHashMap(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::unordered_map<int,int>hm;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)hm[rng()%100000]=i;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPriorityQ(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::priority_queue<int>pq;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)pq.push(rng()%100000);for(int i=0;i<1000;++i)if(!pq.empty())pq.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStack(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::stack<int>st;while(true){for(int i=0;i<1000;++i)st.push(i);for(int i=0;i<1000;++i)if(!st.empty())st.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkQueue(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::queue<int>q;while(true){for(int i=0;i<1000;++i)q.push(i);for(int i=0;i<1000;++i)if(!q.empty())q.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDFS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>>adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back(rng()%V);while(true){std::vector<bool>vis(V,false);std::stack<int>stk;stk.push(0);while(!stk.empty()){int u=stk.top();stk.pop();if(!vis[u]){vis[u]=true;c++;for(int v:adj[u])if(!vis[v])stk.push(v);}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBFS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>>adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back(rng()%V);while(true){std::vector<bool>vis(V,false);std::queue<int>qq;qq.push(0);vis[0]=true;while(!qq.empty()){int u=qq.front();qq.pop();c++;for(int v:adj[u])if(!vis[v]){vis[v]=true;qq.push(v);}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDijkstra(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=50;std::vector<std::vector<std::pair<int,int>>>adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back({rng()%V,rng()%100});while(true){std::vector<int>dist(V,INT_MAX);std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>>pq;dist[0]=0;pq.push({0,0});while(!pq.empty()){int u=pq.top().second;pq.pop();for(auto&e:adj[u]){int v=e.first,w=e.second;if(dist[u]+w<dist[v]){dist[v]=dist[u]+w;pq.push({dist[v],v});c++;}}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFloyd(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=50;std::vector<std::vector<int>>dist(V,std::vector<int>(V,999));std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(i!=j)dist[i][j]=rng()%100;while(true){for(int k=0;k<V;++k)for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(dist[i][j]>dist[i][k]+dist[k][j])dist[i][j]=dist[i][k]+dist[k][j];c+=V*V*V;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkKnapsack(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=100,W=100;std::vector<int>wt(N,1),val(N,1);std::vector<std::vector<int>>K(N+1,std::vector<int>(W+1,0));while(true){for(int i=0;i<=N;++i)for(int w=0;w<=W;++w){if(i==0||w==0)K[i][w]=0;else if(wt[i-1]<=w)K[i][w]=std::max(val[i-1]+K[i-1][w-wt[i-1]],K[i-1][w]);else K[i][w]=K[i-1][w];c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLCS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string X="ABCBDAB",Y="BDCABA";int m=(int)X.size(),n=(int)Y.size();std::vector<std::vector<int>>L(m+1,std::vector<int>(n+1,0));while(true){for(int i=0;i<=m;++i)for(int j=0;j<=n;++j){if(i==0||j==0)L[i][j]=0;else if(X[i-1]==Y[j-1])L[i][j]=L[i-1][j-1]+1;else L[i][j]=std::max(L[i-1][j],L[i][j-1]);c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkEditDist(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s1="kitten",s2="sitting";int m=(int)s1.size(),n=(int)s2.size();std::vector<std::vector<int>>dp(m+1,std::vector<int>(n+1,0));while(true){for(int i=0;i<=m;++i)for(int j=0;j<=n;++j){if(i==0)dp[i][j]=j;else if(j==0)dp[i][j]=i;else if(s1[i-1]==s2[j-1])dp[i][j]=dp[i-1][j-1];else dp[i][j]=1+std::min({dp[i][j-1],dp[i-1][j],dp[i-1][j-1]});c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPrimeFact(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){long long n=rng()%1000000;for(long long i=2;i*i<=n;++i)while(n%i==0){n/=i;c++;}if(n>1)c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}

template<typename Func>
double rodarMultiThread(Func func,int numThreads,int duracao,double fatorEscala){
    auto it=std::chrono::high_resolution_clock::now();
    std::vector<std::future<long long>>futuros;
    DWORD gCount=GetActiveProcessorGroupCount();

    if(gCount>1 && numThreads>64){
        int perGroup=numThreads/(int)gCount;
        int resto=numThreads%(int)gCount;

        for(DWORD g=0;g<gCount;g++){
            int cnt=perGroup+(g<(DWORD)resto?1:0);

            for(int t=0;t<cnt;t++){
                futuros.push_back(std::async(std::launch::async,[func,duracao,g,t]() -> long long {
                    GROUP_AFFINITY ga={};
                    ga.Group=(WORD)g;
                    ga.Mask=(KAFFINITY)1<<(t%64);
                    SetThreadGroupAffinity(GetCurrentThread(),&ga,NULL);
                    return func(duracao);
                }));
            }
        }
    }else{
        for(int t=0;t<numThreads;++t)
            futuros.push_back(std::async(std::launch::async,func,duracao));
    }

    long long total=0;

    for(auto&f:futuros)
        total+=f.get();

    auto ft=std::chrono::high_resolution_clock::now();

    return calcularScoreNormalizado(total,std::chrono::duration<double>(ft-it).count(),fatorEscala);
}

template<typename Func>
double rodarSingleCore(Func func,int duracao,double fatorEscala){
    return rodarMultiThread(func,1,duracao,fatorEscala);
}


// =============================================================================
// MODAL RESUMO - LADO A LADO (MULTI + SINGLE)
// =============================================================================

void CriarFontesModal(){
    if(hFontModalTitulo)DeleteObject(hFontModalTitulo);
    if(hFontModalPct)DeleteObject(hFontModalPct);
    if(hFontModalNome)DeleteObject(hFontModalNome);
    if(hFontModalMsg)DeleteObject(hFontModalMsg);
    if(hFontModalPts)DeleteObject(hFontModalPts);
    if(hFontModalCard)DeleteObject(hFontModalCard);
    if(hFontModalBtn)DeleteObject(hFontModalBtn);
    if(hFontModalVs)DeleteObject(hFontModalVs);

    hFontModalTitulo=CreateFontW(38,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalPct=CreateFontW(80,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalNome=CreateFontW(20,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalMsg=CreateFontW(22,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalPts=CreateFontW(18,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalCard=CreateFontW(15,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalBtn=CreateFontW(22,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontModalVs=CreateFontW(16,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
}

void DestruirFontesModal(){
    if(hFontModalTitulo){DeleteObject(hFontModalTitulo);hFontModalTitulo=NULL;}
    if(hFontModalPct){DeleteObject(hFontModalPct);hFontModalPct=NULL;}
    if(hFontModalNome){DeleteObject(hFontModalNome);hFontModalNome=NULL;}
    if(hFontModalMsg){DeleteObject(hFontModalMsg);hFontModalMsg=NULL;}
    if(hFontModalPts){DeleteObject(hFontModalPts);hFontModalPts=NULL;}
    if(hFontModalCard){DeleteObject(hFontModalCard);hFontModalCard=NULL;}
    if(hFontModalBtn){DeleteObject(hFontModalBtn);hFontModalBtn=NULL;}
    if(hFontModalVs){DeleteObject(hFontModalVs);hFontModalVs=NULL;}
}

void DesenharPainelModal(HDC hdc,RECT&area,bool isMulti,int idxA,int idxB,bool meuPcVsOutro){
    const IdiomaTextos&t=traducoes[currentLangIndex];

    double sA,sB;
    const double*scA,*scB;
    std::wstring nA,nB;

    if(meuPcVsOutro){
        nA=ObterNomeCompletoCPU()+L" ("+std::to_wstring(meuUltimoNumThreads)+L" Threads)";
        nB=pcsCadastrados[idxB].nome;

        scA=isMulti?meuUltimoScoreTestsMulti:meuUltimoScoreTestsSingle;
        scB=isMulti?pcsCadastrados[idxB].scoresMultiCore:pcsCadastrados[idxB].scoresSingleCore;

        sA=TotalParaExibicao(scA);
        sB=TotalParaExibicao(scB);
    }else{
        nA=pcsCadastrados[idxA].nome;
        nB=pcsCadastrados[idxB].nome;

        scA=isMulti?pcsCadastrados[idxA].scoresMultiCore:pcsCadastrados[idxA].scoresSingleCore;
        scB=isMulti?pcsCadastrados[idxB].scoresMultiCore:pcsCadastrados[idxB].scoresSingleCore;

        sA=TotalParaExibicao(scA);
        sB=TotalParaExibicao(scB);
    }

    double sV,sP;
    std::wstring nV,nP;
    const double*scV,*scP;

    if(sA>=sB){
        sV=sA; sP=sB; nV=nA; nP=nB; scV=scA; scP=scB;
    }else{
        sV=sB; sP=sA; nV=nB; nP=nA; scV=scB; scP=scA;
    }

    double diff=0;
    if(sP>0)
        diff=((sV-sP)/sP)*100.0;

    int gV=0,gP=0;

    for(int i=0;i<100;++i){
        double vv=ScoreParaExibicao(i,scV[i]);
        double vp=ScoreParaExibicao(i,scP[i]);

        if(vv>vp)gV++;
        else if(vp>vv)gP++;
    }

    COLORREF cT=isMulti?RGB(0,220,255):RGB(255,165,0);
    COLORREF cPc=RGB(80,255,120);
    COLORREF cBr=isMulti?RGB(0,200,230):RGB(255,140,0);

    SetBkMode(hdc,TRANSPARENT);

    int y=area.top+8;
    HFONT of=(HFONT)SelectObject(hdc,hFontModalTitulo);

    SetTextColor(hdc,cT);
    RECT r={area.left+5,y,area.right-5,y+42};
    DrawTextW(hdc,isMulti?t.modalMultiCore:t.modalSingleCore,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=44;

    SelectObject(hdc,hFontModalVs);
    SetTextColor(hdc,RGB(180,180,180));
    r={area.left+5,y,area.right-5,y+20};
    DrawTextW(hdc,nA.c_str(),-1,&r,DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
    y+=20;

    SetTextColor(hdc,RGB(100,200,255));
    r={area.left+5,y,area.right-5,y+18};
    DrawTextW(hdc,t.modalVs,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=18;

    SetTextColor(hdc,RGB(180,180,180));
    r={area.left+5,y,area.right-5,y+20};
    DrawTextW(hdc,nB.c_str(),-1,&r,DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
    y+=24;

    SelectObject(hdc,hFontModalPct);
    SetTextColor(hdc,cPc);

    wchar_t ps[64];
    swprintf_s(ps,L"+%.1f%%",diff);

    r={area.left+5,y,area.right-5,y+85};
    DrawTextW(hdc,ps,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=85;

    SelectObject(hdc,hFontModalNome);
    SetTextColor(hdc,cPc);
    r={area.left+5,y,area.right-5,y+24};
    DrawTextW(hdc,nV.c_str(),-1,&r,DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
    y+=24;

    SelectObject(hdc,hFontModalMsg);
    SetTextColor(hdc,RGB(255,255,255));
    r={area.left+5,y,area.right-5,y+26};
    DrawTextW(hdc,t.modalMaisRapido,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=30;

    SelectObject(hdc,hFontModalPts);
    SetTextColor(hdc,cT);

    wchar_t pts[128];
    std::wstring sVFmt=FormatarPontosFinal(sV);
    swprintf_s(pts,L"%s: %s",t.modalPts,sVFmt.c_str());

    r={area.left+5,y,area.right-5,y+22};
    DrawTextW(hdc,pts,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=24;

    double mx=(sA>sB)?sA:sB;
    if(mx<=0)mx=1;

    double rat=sV/mx;

    int bl=area.left+15,br=area.right-15,bw=br-bl,bh=16;

    HBRUSH hb=CreateSolidBrush(RGB(40,50,70));
    RECT rb={bl,y,br,y+bh};
    FillRect(hdc,&rb,hb);
    DeleteObject(hb);

    hb=CreateSolidBrush(cBr);
    rb={bl,y,bl+(int)(bw*rat),y+bh};
    FillRect(hdc,&rb,hb);
    DeleteObject(hb);

    y+=bh+10;

    int ch=52;

    hb=CreateSolidBrush(RGB(20,30,50));
    RECT rc2={area.left+8,y,area.right-8,y+ch};
    FillRect(hdc,&rc2,hb);
    DeleteObject(hb);

    HPEN hp=CreatePen(PS_SOLID,1,RGB(60,80,110));
    HPEN op=(HPEN)SelectObject(hdc,hp);
    HBRUSH hn=(HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH ob=(HBRUSH)SelectObject(hdc,hn);

    Rectangle(hdc,rc2.left,rc2.top,rc2.right,rc2.bottom);

    SelectObject(hdc,op);
    SelectObject(hdc,ob);
    DeleteObject(hp);

    SelectObject(hdc,hFontModalCard);
    SetTextColor(hdc,RGB(80,255,120));

    wchar_t l1[512];
    swprintf_s(l1,L"\x2605 %s \x2014 %s %d %s",nV.c_str(),t.modalGanhou,gV,t.modalTestes);

    r={area.left+14,y+3,area.right-14,y+22};
    DrawTextW(hdc,l1,-1,&r,DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS);

    SetTextColor(hdc,RGB(255,100,100));

    wchar_t l2[512];
    swprintf_s(l2,L"\x2620 %s \x2014 %s %d %s",nP.c_str(),t.modalGanhou,gP,t.modalTestes);

    r={area.left+14,y+26,area.right-14,y+45};
    DrawTextW(hdc,l2,-1,&r,DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS);

    SelectObject(hdc,of);
}

LRESULT CALLBACK ModalProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        case WM_ERASEBKGND:{
            HDC h=(HDC)wParam;
            RECT rc;
            GetClientRect(hwnd,&rc);

            HBRUSH hb=CreateSolidBrush(RGB(10,15,30));
            FillRect(h,&rc,hb);
            DeleteObject(hb);

            HPEN hp=CreatePen(PS_SOLID,2,RGB(0,180,220));
            HPEN op=(HPEN)SelectObject(h,hp);
            HBRUSH hn2=(HBRUSH)GetStockObject(NULL_BRUSH);
            HBRUSH ob=(HBRUSH)SelectObject(h,hn2);

            Rectangle(h,1,1,rc.right-1,rc.bottom-1);

            SelectObject(h,op);
            SelectObject(h,ob);
            DeleteObject(hp);

            hp=CreatePen(PS_SOLID,1,RGB(0,120,160));
            op=(HPEN)SelectObject(h,hp);

            MoveToEx(h,rc.right/2,10,NULL);
            LineTo(h,rc.right/2,rc.bottom-70);

            SelectObject(h,op);
            DeleteObject(hp);

            return 1;
        }

        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hwnd,&ps);
            HDC hm=CreateCompatibleDC(hdc);

            RECT rc;
            GetClientRect(hwnd,&rc);

            HBITMAP hbm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
            HBITMAP obm=(HBITMAP)SelectObject(hm,hbm);

            HBRUSH hbr=CreateSolidBrush(RGB(10,15,30));
            FillRect(hm,&rc,hbr);
            DeleteObject(hbr);

            HPEN hp=CreatePen(PS_SOLID,2,RGB(0,180,220));
            HPEN op=(HPEN)SelectObject(hm,hp);
            HBRUSH hn2=(HBRUSH)GetStockObject(NULL_BRUSH);
            HBRUSH obr=(HBRUSH)SelectObject(hm,hn2);

            Rectangle(hm,1,1,rc.right-1,rc.bottom-1);

            SelectObject(hm,op);
            SelectObject(hm,obr);
            DeleteObject(hp);

            hp=CreatePen(PS_SOLID,1,RGB(0,120,160));
            op=(HPEN)SelectObject(hm,hp);

            MoveToEx(hm,rc.right/2,10,NULL);
            LineTo(hm,rc.right/2,rc.bottom-70);

            SelectObject(hm,op);
            DeleteObject(hp);

            RECT lp={5,5,rc.right/2-5,rc.bottom-70};
            DesenharPainelModal(hm,lp,true,g_modalIdxA,g_modalIdxB,g_modalMeuPcVsOutro);

            RECT rp={rc.right/2+5,5,rc.right-5,rc.bottom-70};
            DesenharPainelModal(hm,rp,false,g_modalIdxA,g_modalIdxB,g_modalMeuPcVsOutro);

            BitBlt(hdc,0,0,rc.right,rc.bottom,hm,0,0,SRCCOPY);

            SelectObject(hm,obm);
            DeleteObject(hbm);
            DeleteDC(hm);
            EndPaint(hwnd,&ps);

            return 0;
        }

        case WM_COMMAND:
            if(LOWORD(wParam)==ID_MODAL_BTN_CLOSE)
                FecharModal();
            break;

        case WM_CLOSE:
            FecharModal();
            return 0;
    }

    return DefWindowProcW(hwnd,uMsg,wParam,lParam);
}

void AbrirModalResumo(int idxA,int idxB,bool meuPcVsOutro){
    if(hModalWnd)return;

    g_modalIdxA=idxA;
    g_modalIdxB=idxB;
    g_modalMeuPcVsOutro=meuPcVsOutro;

    CriarFontesModal();

    int mw=1200,mh=620;
    int sw=GetSystemMetrics(SM_CXSCREEN),sh=GetSystemMetrics(SM_CYSCREEN);
    int px=(sw-mw)/2,py=(sh-mh)/2;

    if(px<0)px=0;
    if(py<0)py=0;

    WNDCLASSW wc={};

    wc.lpfnWndProc=ModalProc;
    wc.hInstance=GetModuleHandle(NULL);
    wc.lpszClassName=L"ModalResumoClass";
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground=NULL;

    RegisterClassW(&wc);

    hModalWnd=CreateWindowExW(WS_EX_TOOLWINDOW,L"ModalResumoClass",L"",
        WS_POPUP|WS_VISIBLE,px,py,mw,mh,hMainWnd,NULL,GetModuleHandle(NULL),NULL);

    int bw=180,bh2=48;

    HWND hbc=CreateWindowW(L"BUTTON",traducoes[currentLangIndex].modalFechar,
        WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
        (mw-bw)/2,mh-62,bw,bh2,
        hModalWnd,(HMENU)ID_MODAL_BTN_CLOSE,GetModuleHandle(NULL),NULL);

    SendMessageW(hbc,WM_SETFONT,(WPARAM)hFontModalBtn,TRUE);

    ShowWindow(hModalWnd,SW_SHOW);
    UpdateWindow(hModalWnd);
}

void FecharModal(){
    if(hModalWnd){
        DestroyWindow(hModalWnd);
        hModalWnd=NULL;
    }

    DestruirFontesModal();
}

// =============================================================================
// RANKING
// =============================================================================

void CriarFontesRanking(){
    if(hFontRankTitulo)DeleteObject(hFontRankTitulo);
    if(hFontRankHeader)DeleteObject(hFontRankHeader);
    if(hFontRankNome)DeleteObject(hFontRankNome);
    if(hFontRankPts)DeleteObject(hFontRankPts);
    if(hFontRankBtn)DeleteObject(hFontRankBtn);
    if(hFontRankNum)DeleteObject(hFontRankNum);

    hFontRankTitulo=CreateFontW(42,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontRankHeader=CreateFontW(24,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontRankNome=CreateFontW(16,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontRankPts=CreateFontW(16,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontRankBtn=CreateFontW(22,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
    hFontRankNum=CreateFontW(18,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,L"Arial");
}

void DestruirFontesRanking(){
    if(hFontRankTitulo){DeleteObject(hFontRankTitulo);hFontRankTitulo=NULL;}
    if(hFontRankHeader){DeleteObject(hFontRankHeader);hFontRankHeader=NULL;}
    if(hFontRankNome){DeleteObject(hFontRankNome);hFontRankNome=NULL;}
    if(hFontRankPts){DeleteObject(hFontRankPts);hFontRankPts=NULL;}
    if(hFontRankBtn){DeleteObject(hFontRankBtn);hFontRankBtn=NULL;}
    if(hFontRankNum){DeleteObject(hFontRankNum);hFontRankNum=NULL;}
}

void DesenharColunaRanking(HDC hdc,int colLeft,int colRight,int topY,int bottomY,
std::vector<size_t>&indices,bool isMulti,int scrollOffset){
    const IdiomaTextos&t=traducoes[currentLangIndex];

    COLORREF corH=isMulti?RGB(0,220,255):RGB(255,165,0);
    COLORREF corBr=isMulti?RGB(0,200,230):RGB(255,140,0);

    int lineH=38,headerH=35;

    SetBkMode(hdc,TRANSPARENT);

    HFONT of=(HFONT)SelectObject(hdc,hFontRankHeader);

    SetTextColor(hdc,corH);
    RECT rh={colLeft,topY,colRight,topY+headerH};
    DrawTextW(hdc,isMulti?t.modalMultiCore:t.modalSingleCore,-1,&rh,DT_CENTER|DT_SINGLELINE);

    HPEN hp=CreatePen(PS_SOLID,2,corH);
    HPEN op=(HPEN)SelectObject(hdc,hp);

    MoveToEx(hdc,colLeft+10,topY+headerH-2,NULL);
    LineTo(hdc,colRight-10,topY+headerH-2);

    SelectObject(hdc,op);
    DeleteObject(hp);

    int listTop=topY+headerH+5;
    int maxLines=(bottomY-listTop)/lineH;

    if(maxLines<1)maxLines=1;

    double maxScore=0;

    for(size_t idx:indices){
        double sc=isMulti?TotalParaExibicao(pcsCadastrados[idx].scoresMultiCore):TotalParaExibicao(pcsCadastrados[idx].scoresSingleCore);

        if(sc>maxScore)maxScore=sc;
    }

    if(maxScore<=0)maxScore=1;

    int startIdx=scrollOffset;
    int endIdx=startIdx+maxLines;

    if(endIdx>(int)indices.size())endIdx=(int)indices.size();

    for(int i=startIdx;i<endIdx;i++){
        int rank=i+1;
        size_t idx=indices[i];

        double score=isMulti?TotalParaExibicao(pcsCadastrados[idx].scoresMultiCore):TotalParaExibicao(pcsCadastrados[idx].scoresSingleCore);
        std::wstring nome=pcsCadastrados[idx].nome;

        int ly=listTop+(i-startIdx)*lineH;

        if(rank==1){
            HBRUSH hb=CreateSolidBrush(RGB(60,50,10));
            RECT rbg={colLeft+2,ly,colRight-2,ly+lineH-2};
            FillRect(hdc,&rbg,hb);
            DeleteObject(hb);
        }else if(rank==2){
            HBRUSH hb=CreateSolidBrush(RGB(40,40,50));
            RECT rbg={colLeft+2,ly,colRight-2,ly+lineH-2};
            FillRect(hdc,&rbg,hb);
            DeleteObject(hb);
        }else if(rank==3){
            HBRUSH hb=CreateSolidBrush(RGB(50,35,20));
            RECT rbg={colLeft+2,ly,colRight-2,ly+lineH-2};
            FillRect(hdc,&rbg,hb);
            DeleteObject(hb);
        }

        HPEN hpL=CreatePen(PS_SOLID,1,RGB(40,50,70));
        HPEN opL=(HPEN)SelectObject(hdc,hpL);

        MoveToEx(hdc,colLeft+5,ly+lineH-1,NULL);
        LineTo(hdc,colRight-5,ly+lineH-1);

        SelectObject(hdc,opL);
        DeleteObject(hpL);

        int xC=colLeft+8;

        if(rank==1){
            SelectObject(hdc,hFontRankNum);
            SetTextColor(hdc,RGB(255,215,0));

            RECT rr={xC,ly+2,xC+30,ly+lineH-2};
            DrawTextW(hdc,L"\x265B",-1,&rr,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

            xC+=32;
        }else if(rank<=3){
            SelectObject(hdc,hFontRankNum);
            SetTextColor(hdc,rank==2?RGB(192,192,192):RGB(205,127,50));

            wchar_t rs[16];
            swprintf_s(rs,L"%d",rank);

            RECT rr={xC,ly+2,xC+30,ly+lineH-2};
            DrawTextW(hdc,rs,-1,&rr,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

            xC+=32;
        }else{
            SelectObject(hdc,hFontRankNum);
            SetTextColor(hdc,RGB(150,150,150));

            wchar_t rs[16];
            swprintf_s(rs,L"#%d",rank);

            RECT rr={xC,ly+2,xC+35,ly+lineH-2};
            DrawTextW(hdc,rs,-1,&rr,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

            xC+=37;
        }

        int scoreAreaW=180;
        int nomeRight=colRight-scoreAreaW-10;

        SelectObject(hdc,hFontRankNome);
        SetTextColor(hdc,rank<=3?RGB(255,255,255):RGB(200,200,200));

        RECT rn={xC,ly+2,nomeRight,ly+lineH-2};
        DrawTextW(hdc,nome.c_str(),-1,&rn,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

        SelectObject(hdc,hFontRankPts);
        SetTextColor(hdc,corH);

        wchar_t scStr[128];
        std::wstring scoreFmt=FormatarPontosFinal(score);
        swprintf_s(scStr,L"%s PTS",scoreFmt.c_str());

        int scW=120;

        RECT rsc={colRight-scW-5,ly+2,colRight-5,ly+18};
        DrawTextW(hdc,scStr,-1,&rsc,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

        double ratio=score/maxScore;

        int barL2=colRight-scW-5,barR2=colRight-5,barW2=barR2-barL2;
        int barT=ly+20,barH2=8;

        HBRUSH hbBg=CreateSolidBrush(RGB(40,50,70));
        RECT rbb={barL2,barT,barR2,barT+barH2};
        FillRect(hdc,&rbb,hbBg);
        DeleteObject(hbBg);

        HBRUSH hbF=CreateSolidBrush(corBr);
        RECT rbf={barL2,barT,barL2+(int)(barW2*ratio),barT+barH2};
        FillRect(hdc,&rbf,hbF);
        DeleteObject(hbF);
    }

    if((int)indices.size()>maxLines){
        int sbL=colRight-12,sbT=listTop,sbB=bottomY-5,sbH=sbB-sbT;

        HBRUSH hbTr=CreateSolidBrush(RGB(30,40,60));
        RECT rt2={sbL,sbT,sbL+8,sbB};
        FillRect(hdc,&rt2,hbTr);
        DeleteObject(hbTr);

        double tR=(double)maxLines/(double)indices.size();
        int tH=(int)(sbH*tR);

        if(tH<20)tH=20;

        double sR=(double)scrollOffset/(double)((int)indices.size()-maxLines);
        int tY=sbT+(int)((sbH-tH)*sR);

        HBRUSH hbTh=CreateSolidBrush(corBr);
        RECT rth={sbL,tY,sbL+8,tY+tH};
        FillRect(hdc,&rth,hbTh);
        DeleteObject(hbTh);
    }

    SelectObject(hdc,of);
}

void DesenharRanking(HDC hdc,RECT&rc){
    const IdiomaTextos&t=traducoes[currentLangIndex];

    HBRUSH hb=CreateSolidBrush(RGB(10,15,30));
    FillRect(hdc,&rc,hb);
    DeleteObject(hb);

    HPEN hp=CreatePen(PS_SOLID,2,RGB(0,180,220));
    HPEN op=(HPEN)SelectObject(hdc,hp);
    HBRUSH hn=(HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH ob=(HBRUSH)SelectObject(hdc,hn);

    Rectangle(hdc,1,1,rc.right-1,rc.bottom-1);

    SelectObject(hdc,op);
    SelectObject(hdc,ob);
    DeleteObject(hp);

    SetBkMode(hdc,TRANSPARENT);

    HFONT of=(HFONT)SelectObject(hdc,hFontRankTitulo);
    SetTextColor(hdc,RGB(0,220,255));

    RECT rt={10,10,rc.right-10,55};
    DrawTextW(hdc,t.rankingTitulo,-1,&rt,DT_CENTER|DT_SINGLELINE);

    SelectObject(hdc,of);

    int midX=rc.right/2;

    hp=CreatePen(PS_SOLID,1,RGB(0,120,160));
    op=(HPEN)SelectObject(hdc,hp);

    MoveToEx(hdc,midX,60,NULL);
    LineTo(hdc,midX,rc.bottom-70);

    SelectObject(hdc,op);
    DeleteObject(hp);

    std::vector<size_t>idxM,idxS;

    for(size_t i=1;i<pcsCadastrados.size();++i){
        idxM.push_back(i);
        idxS.push_back(i);
    }

    std::sort(idxM.begin(),idxM.end(),[](size_t a,size_t b){
        return TotalParaExibicao(pcsCadastrados[a].scoresMultiCore)>
               TotalParaExibicao(pcsCadastrados[b].scoresMultiCore);
    });

    std::sort(idxS.begin(),idxS.end(),[](size_t a,size_t b){
        return TotalParaExibicao(pcsCadastrados[a].scoresSingleCore)>
               TotalParaExibicao(pcsCadastrados[b].scoresSingleCore);
    });

    DesenharColunaRanking(hdc,10,midX-5,60,rc.bottom-70,idxM,true,g_rankScrollMulti);
    DesenharColunaRanking(hdc,midX+5,rc.right-10,60,rc.bottom-70,idxS,false,g_rankScrollSingle);
}

LRESULT CALLBACK RankingProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        case WM_ERASEBKGND:{
            HDC h=(HDC)wParam;
            RECT rc;
            GetClientRect(hwnd,&rc);

            HBRUSH hb=CreateSolidBrush(RGB(10,15,30));
            FillRect(h,&rc,hb);
            DeleteObject(hb);

            return 1;
        }

        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hwnd,&ps);
            HDC hm=CreateCompatibleDC(hdc);

            RECT rc;
            GetClientRect(hwnd,&rc);

            HBITMAP hbm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
            HBITMAP obm=(HBITMAP)SelectObject(hm,hbm);

            DesenharRanking(hm,rc);

            BitBlt(hdc,0,0,rc.right,rc.bottom,hm,0,0,SRCCOPY);

            SelectObject(hm,obm);
            DeleteObject(hbm);
            DeleteDC(hm);
            EndPaint(hwnd,&ps);

            return 0;
        }

        case WM_MOUSEWHEEL:{
            int delta=GET_WHEEL_DELTA_WPARAM(wParam);

            POINT pt;
            pt.x=(short)LOWORD(lParam);
            pt.y=(short)HIWORD(lParam);

            ScreenToClient(hwnd,&pt);

            RECT rc;
            GetClientRect(hwnd,&rc);

            int midX=rc.right/2;

            int maxS=(int)pcsCadastrados.size()-1-10;
            if(maxS<0)maxS=0;

            if(pt.x<midX){
                g_rankScrollMulti-=(delta>0)?3:-3;

                if(g_rankScrollMulti<0)g_rankScrollMulti=0;
                if(g_rankScrollMulti>maxS)g_rankScrollMulti=maxS;
            }else{
                g_rankScrollSingle-=(delta>0)?3:-3;

                if(g_rankScrollSingle<0)g_rankScrollSingle=0;
                if(g_rankScrollSingle>maxS)g_rankScrollSingle=maxS;
            }

            InvalidateRect(hwnd,NULL,TRUE);

            return 0;
        }

        case WM_COMMAND:
            if(LOWORD(wParam)==ID_RANKING_BTN_CLOSE)
                FecharRanking();
            break;

        case WM_CLOSE:
            FecharRanking();
            return 0;
    }

    return DefWindowProcW(hwnd,uMsg,wParam,lParam);
}

void AbrirRanking(){
    if(hRankingWnd)return;

    g_rankScrollMulti=0;
    g_rankScrollSingle=0;

    CriarFontesRanking();

    int rw=1450,rh=750;
    int sw=GetSystemMetrics(SM_CXSCREEN),sh=GetSystemMetrics(SM_CYSCREEN);
    int px=(sw-rw)/2,py=(sh-rh)/2;

    if(px<0)px=0;
    if(py<0)py=0;

    WNDCLASSW wc={};

    wc.lpfnWndProc=RankingProc;
    wc.hInstance=GetModuleHandle(NULL);
    wc.lpszClassName=L"RankingClass";
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground=NULL;

    RegisterClassW(&wc);

    hRankingWnd=CreateWindowExW(WS_EX_TOOLWINDOW,L"RankingClass",L"",
        WS_POPUP|WS_VISIBLE,px,py,rw,rh,hMainWnd,NULL,GetModuleHandle(NULL),NULL);

    int bw=180,bh2=48;

    HWND hbc=CreateWindowW(L"BUTTON",traducoes[currentLangIndex].rankingFechar,
        WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
        (rw-bw)/2,rh-60,bw,bh2,
        hRankingWnd,(HMENU)ID_RANKING_BTN_CLOSE,GetModuleHandle(NULL),NULL);

    SendMessageW(hbc,WM_SETFONT,(WPARAM)hFontRankBtn,TRUE);

    ShowWindow(hRankingWnd,SW_SHOW);
    UpdateWindow(hRankingWnd);
}

void FecharRanking(){
    if(hRankingWnd){
        DestroyWindow(hRankingWnd);
        hRankingWnd=NULL;
    }

    DestruirFontesRanking();
}

void VerificarBotoesResumo(){
    bool cA=false,cB=false;

    if(hComboCpuA){
        int p=(int)SendMessageW(hComboCpuA,CB_GETCURSEL,0,0);

        if(p>=0){
            int idx=(int)SendMessageW(hComboCpuA,CB_GETITEMDATA,p,0);

            if(idx>0)cA=true;
        }
    }

    if(hComboCpuB){
        int p=(int)SendMessageW(hComboCpuB,CB_GETCURSEL,0,0);

        if(p>=0){
            int idx=(int)SendMessageW(hComboCpuB,CB_GETITEMDATA,p,0);

            if(idx>0)cB=true;
        }
    }

    if(cA&&cB)
        ShowWindow(hBtnResumo,SW_SHOW);
    else
        ShowWindow(hBtnResumo,SW_HIDE);

    if(benchmarkRealizado){
        int p=(int)SendMessageW(hComboCompare,CB_GETCURSEL,0,0);

        if(p>=0){
            int idx=(int)SendMessageW(hComboCompare,CB_GETITEMDATA,p,0);

            if(idx>0)
                ShowWindow(hBtnVerResultado,SW_SHOW);
            else
                ShowWindow(hBtnVerResultado,SW_HIDE);
        }
    }else{
        ShowWindow(hBtnVerResultado,SW_HIDE);
    }
}

// =============================================================================
// UI PRINCIPAL
// =============================================================================

int MedirTextoLargura(HFONT fonte,const wchar_t*texto){
    if(!fonte||!texto)return 0;

    HDC hdc=GetDC(NULL);
    HFONT a=(HFONT)SelectObject(hdc,fonte);

    SIZE sz;
    GetTextExtentPoint32W(hdc,texto,(int)wcslen(texto),&sz);

    SelectObject(hdc,a);
    ReleaseDC(NULL,hdc);

    return sz.cx;
}

void PosicionarControlesTopo(){
    if(!hStaticLang||!hFontAtual)return;

    double esc=currentFontSize/14.0;

    int aC=(int)(25*esc),aB2=(int)(30*esc),pad=(int)(16*esc);
    int eL=(int)(6*esc),eC=(int)(12*esc);
    int aL=((aC>aB2)?aC:aB2)+(int)(8*esc);

    int x=15,y=15,lim=g_winW-15;

    int wCL=(int)(150*esc),wCC=(int)(280*esc);
    int wCA=(int)(430*esc),wCB=(int)(430*esc);

    auto cp=[&](HWND l,HWND c,const wchar_t*t,int w){
        int wl=MedirTextoLargura(hFontAtual,t)+pad;
        int tn=wl+eL+w+eC;

        if(x+tn>lim&&x>15){
            x=15;
            y+=aL;
        }

        if(l)MoveWindow(l,x,y,wl,aC,TRUE);

        x+=wl+eL;

        if(c)MoveWindow(c,x,y,w,250,TRUE);

        x+=w+eC;
    };

    cp(hStaticLang,hComboLang,traducoes[currentLangIndex].labelLang,wCL);
    cp(hStaticCompare,hComboCompare,traducoes[currentLangIndex].labelCompare,wCC);
    cp(hStaticCpuA,hComboCpuA,traducoes[currentLangIndex].labelCpuA,wCA);
    cp(hStaticCpuB,hComboCpuB,traducoes[currentLangIndex].labelCpuB,wCB);

    x=15;
    y+=aL;

    int wBtn=MedirTextoLargura(hFontAtual,traducoes[currentLangIndex].btnRun)+(int)(30*esc);

    if(wBtn<(int)(90*esc))wBtn=(int)(90*esc);

    if(hBtnRun)MoveWindow(hBtnRun,x,y,wBtn,aB2,TRUE);

    x+=wBtn+eC;

    int wBR=(int)(130*esc);

    if(hBtnResumo)MoveWindow(hBtnResumo,x,y,wBR,aB2,TRUE);

    x+=wBR+eC;

    if(hBtnVerResultado)MoveWindow(hBtnVerResultado,x,y,wBR,aB2,TRUE);

    x+=wBR+eC;

    if(hBtnRanking)MoveWindow(hBtnRanking,x,y,wBR,aB2,TRUE);

    y+=aL+(int)(4*esc);

    if(hStaticStatus)MoveWindow(hStaticStatus,15,y,g_winW-30,aC,TRUE);

    y+=aC+(int)(15*esc);

    int aLog=g_winH-y-15;

    if(aLog<260)aLog=260;

    if(hEditLog)MoveWindow(hEditLog,15,y,g_winW-30,aLog,TRUE);
}

void AtualizarFontesSimples(int fs){
    currentFontSize=fs;

    if(hFontAtual)DeleteObject(hFontAtual);

    hFontAtual=CreateFontW(
        fs,
        0,
        0,
        0,
        FW_MEDIUM,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH|FF_DONTCARE,
        L"Arial"
    );

    HWND ctr[]={
        hStaticLang,
        hComboLang,
        hStaticCompare,
        hComboCompare,
        hStaticCpuA,
        hComboCpuA,
        hStaticCpuB,
        hComboCpuB,
        hBtnRun,
        hStaticStatus,
        hBtnResumo,
        hBtnVerResultado,
        hBtnRanking
    };

    for(HWND h:ctr){
        if(h)SendMessageW(h,WM_SETFONT,(WPARAM)hFontAtual,TRUE);
    }

    if(hEditLog){
        CHARFORMAT2W cf={0};
        cf.cbSize=sizeof(cf);

        cf.dwMask=CFM_SIZE|CFM_FACE|CFM_COLOR|CFM_WEIGHT;
        cf.yHeight=fs*10;
        cf.wWeight=FW_MEDIUM;

        wcscpy_s(cf.szFaceName,L"Consolas");

        cf.crTextColor=RGB(0,0,0);
        cf.dwEffects=0;

        SendMessageW(hEditLog,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&cf);
    }

    InvalidateRect(GetParent(hStaticLang),NULL,TRUE);
    PosicionarControlesTopo();
}

void AtualizarIdiomaInterface(int li){
    currentLangIndex=li;

    SetWindowTextW(GetParent(hStaticLang),traducoes[li].tituloJanela);
    SetWindowTextW(hStaticLang,traducoes[li].labelLang);
    SetWindowTextW(hStaticCompare,traducoes[li].labelCompare);
    SetWindowTextW(hBtnRun,traducoes[li].btnRun);
    SetWindowTextW(hStaticCpuA,traducoes[li].labelCpuA);
    SetWindowTextW(hStaticCpuB,traducoes[li].labelCpuB);

    if(hBtnResumo)SetWindowTextW(hBtnResumo,traducoes[li].btnResumo);
    if(hBtnVerResultado)SetWindowTextW(hBtnVerResultado,traducoes[li].btnVerResultado);
    if(hBtnRanking)SetWindowTextW(hBtnRanking,traducoes[li].btnRanking);

    if(GetWindowTextLengthW(hStaticStatus)>0)
        SetWindowTextW(hStaticStatus,traducoes[li].statusPronto);

    if(pcsCadastrados.size()>0)
        pcsCadastrados[0].nome=traducoes[li].selecionePC;

    AtualizarListaComparacao();
    AtualizarPainelPrincipal();
    PosicionarControlesTopo();
    VerificarBotoesResumo();
}

void AtualizarListaComparacao(){
    SendMessageW(hComboCompare,CB_RESETCONTENT,0,0);

    if(hComboCpuA)SendMessageW(hComboCpuA,CB_RESETCONTENT,0,0);
    if(hComboCpuB)SendMessageW(hComboCpuB,CB_RESETCONTENT,0,0);

    if(pcsCadastrados.empty())return;

    std::vector<size_t>idx;

    for(size_t i=1;i<pcsCadastrados.size();++i)
        idx.push_back(i);

    std::sort(idx.begin(),idx.end(),[](size_t a,size_t b){
        return TotalParaExibicao(pcsCadastrados[a].scoresMultiCore)>
               TotalParaExibicao(pcsCadastrados[b].scoresMultiCore);
    });

    auto pc=[&](HWND c){
        if(!c)return;

        int p=(int)SendMessageW(c,CB_ADDSTRING,0,(LPARAM)pcsCadastrados[0].nome.c_str());
        SendMessageW(c,CB_SETITEMDATA,p,(LPARAM)0);

        for(size_t i:idx){
            p=(int)SendMessageW(c,CB_ADDSTRING,0,(LPARAM)pcsCadastrados[i].nome.c_str());
            SendMessageW(c,CB_SETITEMDATA,p,(LPARAM)i);
        }

        SendMessageW(c,CB_SETCURSEL,0,0);
    };

    pc(hComboCompare);
    pc(hComboCpuA);
    pc(hComboCpuB);
}

void AtualizarPainelComparativo(){
    if(!benchmarkRealizado){
        SetWindowTextW(hEditLog,traducoes[currentLangIndex].avisoRodarPrimeiro);
        return;
    }

    int pos=(int)SendMessageW(hComboCompare,CB_GETCURSEL,0,0);
    int ci=-1;

    if(pos>=0)
        ci=(int)SendMessageW(hComboCompare,CB_GETITEMDATA,pos,0);

    bool tc=(ci>0&&ci<(int)pcsCadastrados.size());

    std::wstring lt=L"";

    lt+=L"===============================================================\r\n";
    lt+=traducoes[currentLangIndex].headerResult;
    lt+=L"\r\n===============================================================\r\n\r\n";

    double totalMeuMultiVis=TotalParaExibicao(meuUltimoScoreTestsMulti);
    double totalMeuSingleVis=TotalParaExibicao(meuUltimoScoreTestsSingle);

    double totalOutroMultiVis=0.0;
    double totalOutroSingleVis=0.0;

    if(tc){
        totalOutroMultiVis=TotalParaExibicao(pcsCadastrados[ci].scoresMultiCore);
        totalOutroSingleVis=TotalParaExibicao(pcsCadastrados[ci].scoresSingleCore);
    }

    lt+=traducoes[currentLangIndex].compMultiCore;
    lt+=L"\r\n";

    {
        wchar_t c[512];

        if(tc)
            swprintf_s(c,L"%-35s | %15s | %15s | %10s\r\n",
                traducoes[currentLangIndex].colTeste,
                traducoes[currentLangIndex].colSeuPC,
                traducoes[currentLangIndex].colOutroPC,
                traducoes[currentLangIndex].colDif);
        else
            swprintf_s(c,L"%-35s | %15s\r\n",
                traducoes[currentLangIndex].colTeste,
                traducoes[currentLangIndex].colSeuPC);

        lt+=c;
        g_cabecalhoAtual=c;
        g_modoCpuXCpuAtivo=false;
    }

    lt+=L"-----------------------------------------------------------------------\r\n";

    for(int i=0;i<100;++i){
        wchar_t l[512];

        double meuVis=ScoreParaExibicao(i,meuUltimoScoreTestsMulti[i]);
        std::wstring meuFmt=FormatarNumero2Decimais(meuVis);

        if(tc){
            double outroVis=ScoreParaExibicao(i,pcsCadastrados[ci].scoresMultiCore[i]);
            std::wstring outroFmt=FormatarNumero2Decimais(outroVis);

            double d=0.0;
if(meuVis>0.0 && outroVis>0.0){
double maior=(meuVis>outroVis)?meuVis:outroVis;
double menor=(meuVis<outroVis)?meuVis:outroVis;
if(menor>0.0) d=((maior-menor)/menor)*100.0;
}

            std::wstring dFmt=FormatarNumero2Decimais(d);

            swprintf_s(l,L"%-35s | %15s | %15s | %10s%%\r\n",
                nomesTestesPT[i],
                meuFmt.c_str(),
                outroFmt.c_str(),
                dFmt.c_str());
        }else{
            swprintf_s(l,L"%-35s | %15s\r\n",
                nomesTestesPT[i],
                meuFmt.c_str());
        }

        lt+=l;
    }

    wchar_t t2[512];
    double dtm=0.0;
    std::wstring dtmFmt;

    std::wstring totalMeuFmt=FormatarPontosFinal(totalMeuMultiVis);

    if(tc){
        std::wstring totalOutroFmt=FormatarPontosFinal(totalOutroMultiVis);

        if(totalOutroMultiVis>0.0)
            dtm=((totalMeuMultiVis-totalOutroMultiVis)/totalOutroMultiVis)*100.0;

        dtmFmt=FormatarNumero2Decimais(dtm<0.0?-dtm:dtm);

        std::wstring totalMeuPts=totalMeuFmt+L" PTS";
        std::wstring totalOutroPts=totalOutroFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s | %15s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuPts.c_str(),
            totalOutroPts.c_str(),
            dtmFmt.c_str());
    }else{
        std::wstring totalMeuPts=totalMeuFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuPts.c_str());
    }

    lt+=t2;
    lt+=L"\r\n";

    lt+=traducoes[currentLangIndex].compSingleCore;
    lt+=L"\r\n";

    {
        wchar_t c[512];

        if(tc)
            swprintf_s(c,L"%-35s | %15s | %15s | %10s\r\n",
                traducoes[currentLangIndex].colTeste,
                traducoes[currentLangIndex].colSeuPC,
                traducoes[currentLangIndex].colOutroPC,
                traducoes[currentLangIndex].colDif);
        else
            swprintf_s(c,L"%-35s | %15s\r\n",
                traducoes[currentLangIndex].colTeste,
                traducoes[currentLangIndex].colSeuPC);

        lt+=c;
    }

    lt+=L"-----------------------------------------------------------------------\r\n";

    for(int i=0;i<100;++i){
        wchar_t l[512];

        double meuVis=ScoreParaExibicao(i,meuUltimoScoreTestsSingle[i]);
        std::wstring meuFmt=FormatarNumero2Decimais(meuVis);

        if(tc){
            double outroVis=ScoreParaExibicao(i,pcsCadastrados[ci].scoresSingleCore[i]);
            std::wstring outroFmt=FormatarNumero2Decimais(outroVis);

            double d=0.0;
if(meuVis>0.0 && outroVis>0.0){
double maior=(meuVis>outroVis)?meuVis:outroVis;
double menor=(meuVis<outroVis)?meuVis:outroVis;
if(menor>0.0) d=((maior-menor)/menor)*100.0;
}

            std::wstring dFmt=FormatarNumero2Decimais(d);

            swprintf_s(l,L"%-35s | %15s | %15s | %10s%%\r\n",
                nomesTestesPT[i],
                meuFmt.c_str(),
                outroFmt.c_str(),
                dFmt.c_str());
        }else{
            swprintf_s(l,L"%-35s | %15s\r\n",
                nomesTestesPT[i],
                meuFmt.c_str());
        }

        lt+=l;
    }

    double dts=0.0;

    std::wstring totalMeuSingleFmt=FormatarPontosFinal(totalMeuSingleVis);

    if(tc){
        std::wstring totalOutroSingleFmt=FormatarPontosFinal(totalOutroSingleVis);

        if(totalOutroSingleVis>0.0)
            dts=((totalMeuSingleVis-totalOutroSingleVis)/totalOutroSingleVis)*100.0;

        std::wstring dtsFmt=FormatarNumero2Decimais(dts<0.0?-dts:dts);

        std::wstring totalMeuSinglePts=totalMeuSingleFmt+L" PTS";
        std::wstring totalOutroSinglePts=totalOutroSingleFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s | %15s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuSinglePts.c_str(),
            totalOutroSinglePts.c_str(),
            dtsFmt.c_str());
    }else{
        std::wstring totalMeuSinglePts=totalMeuSingleFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuSinglePts.c_str());
    }

    lt+=t2;
    lt+=L"\r\n=================================================================\r\n";

    if(tc){
        if(dtm>0){
            lt+=L"\r\n";
            lt+=traducoes[currentLangIndex].msgMaisRapido;

            wchar_t b[100];
            swprintf_s(b,L"%s%%) ***\r\n",dtmFmt.c_str());
            lt+=b;
        }else if(dtm<0){
            lt+=L"\r\n";
            lt+=traducoes[currentLangIndex].msgMaisLento;

            wchar_t b[100];
            swprintf_s(b,L"%s%%) ***\r\n",dtmFmt.c_str());
            lt+=b;
        }else{
            lt+=L"\r\n";
            lt+=traducoes[currentLangIndex].msgEmpate;
            lt+=L"\r\n";
        }
    }else{
        lt+=L"\r\n";
        lt+=traducoes[currentLangIndex].msgSelecioneParaComparar;
        lt+=L"\r\n";
    }

    lt+=L"=================================================================\r\n";

    SetWindowTextW(hEditLog,lt.c_str());

    g_linhaDestacada=-1;
    FormatarLogComparacao();
}

void AtualizarPainelComparativoCpuXCpu(int idxA,int idxB){
    if(idxA<=0||idxB<=0||
       idxA>=(int)pcsCadastrados.size()||
       idxB>=(int)pcsCadastrados.size()||
       idxA==idxB)
        return;

    const PCReferencia&a=pcsCadastrados[idxA];
    const PCReferencia&b=pcsCadastrados[idxB];

    std::wstring lt=L"";

    lt+=L"===============================================================\r\n";
    lt+=traducoes[currentLangIndex].headerResult;
    lt+=L"\r\n===============================================================\r\n\r\n";

    for(int s=0;s<2;++s){
        bool m=(s==0);

        lt+=m?traducoes[currentLangIndex].compMultiCore:traducoes[currentLangIndex].compSingleCore;
        lt+=L"\r\n";

        {
            wchar_t c[512];

            swprintf_s(c,L"%-35s | %55.55s | %55.55s | %10s\r\n",
                traducoes[currentLangIndex].colTeste,
                a.nome.c_str(),
                b.nome.c_str(),
                traducoes[currentLangIndex].colDif);

            lt+=c;

            if(s==0){
                g_cabecalhoAtual=c;
                g_modoCpuXCpuAtivo=true;
            }
        }

        lt+=L"---------------------------------------------------------------------------------------------------------------------------\r\n";

        const double* sA=m?a.scoresMultiCore:a.scoresSingleCore;
        const double* sB=m?b.scoresMultiCore:b.scoresSingleCore;

        for(int i=0;i<100;++i){
            wchar_t l[512];

            double vA=ScoreParaExibicao(i,sA[i]);
            double vB=ScoreParaExibicao(i,sB[i]);

            std::wstring vAFmt=FormatarNumero2Decimais(vA);
            std::wstring vBFmt=FormatarNumero2Decimais(vB);

            double d=0.0;

            if(vA>0.0&&vB>0.0){
                double ma=(vA>vB)?vA:vB;
                double me=(vA<vB)?vA:vB;

                d=((ma-me)/me)*100.0;
            }

            std::wstring dFmt=FormatarNumero2Decimais(d);

            swprintf_s(l,L"%-35s | %55s | %55s | %10s%%\r\n",
                nomesTestesPT[i],
                vAFmt.c_str(),
                vBFmt.c_str(),
                dFmt.c_str());

            lt+=l;
        }

        double tA=m?TotalParaExibicao(a.scoresMultiCore):TotalParaExibicao(a.scoresSingleCore);
        double tB=m?TotalParaExibicao(b.scoresMultiCore):TotalParaExibicao(b.scoresSingleCore);

        double dT=0.0;

        if(tA>0.0&&tB>0.0){
            double ma2=(tA>tB)?tA:tB;
            double me2=(tA<tB)?tA:tB;

            dT=((ma2-me2)/me2)*100.0;
        }

        std::wstring tAFmt=FormatarPontosFinal(tA);
        std::wstring tBFmt=FormatarPontosFinal(tB);
        std::wstring dTFmt=FormatarNumero2Decimais(dT);

        wchar_t ts[512];

        std::wstring tAPts=tAFmt+L" PTS";
        std::wstring tBPts=tBFmt+L" PTS";

        swprintf_s(ts,L"\r\n%-35s | %55s | %55s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            tAPts.c_str(),
            tBPts.c_str(),
            dTFmt.c_str());

        lt+=ts;
        lt+=L"\r\n";
    }

    lt+=L"=================================================================\r\n";

    SetWindowTextW(hEditLog,lt.c_str());

    g_linhaDestacada=-1;
    FormatarLogComparacao();
}

void ObterSelecaoCpuXCpu(int&idxA,int&idxB){
    idxA=-1;
    idxB=-1;

    if(hComboCpuA){
        int p=(int)SendMessageW(hComboCpuA,CB_GETCURSEL,0,0);

        if(p>=0)
            idxA=(int)SendMessageW(hComboCpuA,CB_GETITEMDATA,p,0);
    }

    if(hComboCpuB){
        int p=(int)SendMessageW(hComboCpuB,CB_GETCURSEL,0,0);

        if(p>=0)
            idxB=(int)SendMessageW(hComboCpuB,CB_GETITEMDATA,p,0);
    }
}

void AtualizarPainelPrincipal(){
    int iA=-1,iB=-1;

    ObterSelecaoCpuXCpu(iA,iB);

    bool mc=(iA>0&&iB>0&&
             iA<(int)pcsCadastrados.size()&&
             iB<(int)pcsCadastrados.size()&&
             iA!=iB);

    if(mc)
        AtualizarPainelComparativoCpuXCpu(iA,iB);
    else if(benchmarkRealizado)
        AtualizarPainelComparativo();

    VerificarBotoesResumo();
}

void ExecutarBenchmarkThread(HWND hwnd,int langIndex){
    benchmarkEmAndamento=true;

    try{
        EnableWindow(hBtnRun,FALSE);
        EnableWindow(hComboLang,FALSE);
        EnableWindow(hComboCompare,FALSE);

        if(hComboFont)EnableWindow(hComboFont,FALSE);

        if(hBtnResumo)EnableWindow(hBtnResumo,FALSE);
        if(hBtnVerResultado)EnableWindow(hBtnVerResultado,FALSE);
        if(hBtnRanking)EnableWindow(hBtnRanking,FALSE);

        HMENU hM=GetSystemMenu(hwnd,FALSE);

        if(hM)EnableMenuItem(hM,SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);

        unsigned int nT=0;

        for(int i=0;i<2048;i++){
            wchar_t path[128];
            swprintf_s(path,L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\%d",i);

            HKEY hK2;

            if(RegOpenKeyExW(HKEY_LOCAL_MACHINE,path,0,KEY_READ,&hK2)==ERROR_SUCCESS){
                nT++;
                RegCloseKey(hK2);
            }else{
                break;
            }
        }

        unsigned int hc=std::thread::hardware_concurrency();

        if(hc>nT)nT=hc;

        if(nT==0)nT=4;
        if(nT>4000)nT=4000;

        long long(*tf[100])(int)={
            benchmarkPontoFlutuante,benchmarkMatrizInteiros,benchmarkOrdenacao,benchmarkPrimos,
            benchmarkAlocacaoMemoria,benchmarkBitwise,benchmarkHashSimulado,benchmarkCacheStress,
            benchmarkPolinomios,benchmarkLogicaArray,benchmarkCriptografia,benchmarkCompressao,
            benchmarkFisica,benchmarkGameOfLife,benchmarkAudio,benchmarkRede,benchmarkIA,
            benchmarkDatabase,benchmarkParticulas,benchmarkSteganografia,benchmarkMandelbrot,
            benchmarkFourier,benchmarkShortestPath,benchmarkRegex,benchmarkXML,
            benchmarkMultiplicacaoMatriz,benchmarkRayTracing,benchmarkGenetico,benchmarkFluidos,
            benchmarkAESSimulado,benchmarkAStar,benchmarkMonteCarlo,benchmarkConvolucao,
            benchmarkBTree,benchmarkTensor,benchmarkFatorial,benchmarkFibonacci,benchmarkHanoi,
            benchmarkCrivo,benchmarkMDC,benchmarkPotenciaMod,benchmarkRaizNewton,
            benchmarkSenoTaylor,benchmarkExpMath,benchmarkLogNat,benchmarkAbsBulk,
            benchmarkRoundBulk,benchmarkClamp,benchmarkLerp,benchmarkSpline,benchmarkBubbleSort,
            benchmarkInsertionSort,benchmarkSelectionSort,benchmarkQuickSort,benchmarkMergeSort,
            benchmarkHeapSort,benchmarkCountingSort,benchmarkRadixSort,benchmarkBucketSort,
            benchmarkShellSort,benchmarkStrCopy,benchmarkStrConcat,benchmarkStrCmp,
            benchmarkStrFind,benchmarkStrRev,benchmarkStrUpper,benchmarkStrTrim,
            benchmarkCSVParse,benchmarkJSONToken,benchmarkBase64Enc,benchmarkHexDump,
            benchmarkCRC32,benchmarkAdler32,benchmarkFletcher,benchmarkXORCipher,benchmarkROT13,
            benchmarkCaesar,benchmarkVigenere,benchmarkRandomFill,benchmarkMemSet,
            benchmarkMemMove,benchmarkVecAdd,benchmarkVecDot,benchmarkVecCross,benchmarkMatDet,
            benchmarkMatInv,benchmarkLLTraverse,benchmarkBST,benchmarkHashMap,benchmarkPriorityQ,
            benchmarkStack,benchmarkQueue,benchmarkDFS,benchmarkBFS,benchmarkDijkstra,
            benchmarkFloyd,benchmarkKnapsack,benchmarkLCS,benchmarkEditDist,benchmarkPrimeFact
        };

        double fe[100]={
            500000.0,50000.0,200000.0,10000.0,800000.0,1000000.0,500000.0,300000.0,400000.0,600000.0,
            200000.0,300000.0,150000.0,100000.0,400000.0,500000.0,250000.0,10000.0,200000.0,300000.0,
            50000.0,1000.0,50000.0,1000000.0,500000.0,10000.0,5000.0,50000.0,200000.0,100000.0,
            50000.0,50000.0,100000.0,10000.0,5000.0,1000.0,1000.0,100.0,100000.0,10000.0,
            1000.0,10000.0,10000.0,1000.0,1000.0,100000.0,100000.0,100000.0,100000.0,10000.0,
            10000.0,10000.0,10000.0,10000.0,10000.0,10000.0,10000.0,10000.0,10000.0,10000.0,
            100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,
            100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,
            100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,
            100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0,100000.0
        };

        int dpT=1;

        meuUltimoTotalMulti=0;
        meuUltimoTotalSingle=0;
        meuUltimoNumThreads=nT;

        SetWindowTextW(hStaticStatus,traducoes[langIndex].statusRodandoMulti);

        std::wstring lt=std::wstring(traducoes[langIndex].compMultiCore)+L" - "+
        traducoes[langIndex].lblThreads+std::to_wstring(nT)+L"\r\n\r\n";

        {
            wchar_t c[256];

            swprintf_s(c,L"%-35s | %15s\r\n",
                traducoes[langIndex].colTeste,
                traducoes[langIndex].colPontuacao);

            lt+=c;
        }

        lt+=L"-----------------------------------------------------------------------\r\n";

        SetWindowTextW(hEditLog,lt.c_str());

        for(int i=0;i<100;++i){
            double sm=rodarMultiThread(tf[i],nT,dpT,fe[i]);

            meuUltimoScoreTestsMulti[i]=sm;
            meuUltimoTotalMulti+=sm;

            double smVis=ScoreParaExibicao(i,sm);
            std::wstring smFmt=FormatarNumero2Decimais(smVis);

            wchar_t l[256];
            swprintf_s(l,L"%-35s | %15s\r\n",nomesTestesPT[i],smFmt.c_str());
            lt+=l;

            SetWindowTextW(hEditLog,lt.c_str());

            SendMessageW(hEditLog,EM_SETSEL,(WPARAM)-1,(LPARAM)-1);
            SendMessageW(hEditLog,EM_SCROLLCARET,0,0);

            wchar_t st[256];
            swprintf_s(st,L"%s %d/100",traducoes[langIndex].compMultiCore,i+1);

            SetWindowTextW(hStaticStatus,st);
        }

        SetWindowTextW(hStaticStatus,traducoes[langIndex].statusRodandoSingle);

        lt+=L"\r\n";
        lt+=traducoes[langIndex].compSingleCore;
        lt+=L"\r\n\r\n";

        {
            wchar_t c[256];

            swprintf_s(c,L"%-35s | %15s\r\n",
                traducoes[langIndex].colTeste,
                traducoes[langIndex].colPontuacao);

            lt+=c;
        }

        lt+=L"-----------------------------------------------------------------------\r\n";

        SetWindowTextW(hEditLog,lt.c_str());

        SendMessageW(hEditLog,EM_SETSEL,(WPARAM)-1,(LPARAM)-1);
        SendMessageW(hEditLog,EM_SCROLLCARET,0,0);

        for(int i=0;i<100;++i){
            double ss=rodarSingleCore(tf[i],dpT,fe[i]);

            meuUltimoScoreTestsSingle[i]=ss;
            meuUltimoTotalSingle+=ss;

            double ssVis=ScoreParaExibicao(i,ss);
            std::wstring ssFmt=FormatarNumero2Decimais(ssVis);

            wchar_t l[256];
            swprintf_s(l,L"%-35s | %15s\r\n",nomesTestesPT[i],ssFmt.c_str());
            lt+=l;

            SetWindowTextW(hEditLog,lt.c_str());

            SendMessageW(hEditLog,EM_SETSEL,(WPARAM)-1,(LPARAM)-1);
            SendMessageW(hEditLog,EM_SCROLLCARET,0,0);

            wchar_t st[256];
            swprintf_s(st,L"%s %d/100",traducoes[langIndex].compSingleCore,i+1);

            SetWindowTextW(hStaticStatus,st);
        }

        benchmarkRealizado=true;

        meuUltimoTotalMulti=TotalParaExibicao(meuUltimoScoreTestsMulti);
meuUltimoTotalSingle=TotalParaExibicao(meuUltimoScoreTestsSingle);
std::wstring cpu=ObterNomeCompletoCPU();
        std::wstring nrpc=cpu+L" ("+std::to_wstring(nT)+L" Threads)";

        bool nR=false,en=false;

        for(size_t i=1;i<pcsCadastrados.size();++i){
            if(pcsCadastrados[i].nome==nrpc){
                en=true;

                if(meuUltimoTotalMulti>TotalParaExibicao(pcsCadastrados[i].scoresMultiCore)){
                    pcsCadastrados[i].totalMultiCore=meuUltimoTotalMulti;
                    pcsCadastrados[i].numThreads=nT;

                    for(int j=0;j<100;++j)
                        pcsCadastrados[i].scoresMultiCore[j]=meuUltimoScoreTestsMulti[j];

                    nR=true;
                }

                if(meuUltimoTotalSingle>TotalParaExibicao(pcsCadastrados[i].scoresSingleCore)){
                    pcsCadastrados[i].totalSingleCore=meuUltimoTotalSingle;

                    for(int j=0;j<100;++j)
                        pcsCadastrados[i].scoresSingleCore[j]=meuUltimoScoreTestsSingle[j];

                    nR=true;
                }

                break;
            }
        }

        if(!en){
            PCReferencia np;

            np.nome=nrpc;
            np.numThreads=nT;
            np.totalMultiCore=meuUltimoTotalMulti;
            np.totalSingleCore=meuUltimoTotalSingle;

            for(int i=0;i<100;++i){
                np.scoresMultiCore[i]=meuUltimoScoreTestsMulti[i];
                np.scoresSingleCore[i]=meuUltimoScoreTestsSingle[i];
            }

            pcsCadastrados.push_back(np);
            nR=true;
        }

        if(nR)
            SalvarListaNuvemNativo();

        AtualizarListaComparacao();

        ShowWindow(hStaticCompare,SW_SHOW);
        ShowWindow(hComboCompare,SW_SHOW);

        SetWindowTextW(hStaticStatus,traducoes[langIndex].statusPronto);

        if(IsWindow(hwnd)){
            EnableWindow(hBtnRun,TRUE);
            EnableWindow(hComboLang,TRUE);
            EnableWindow(hComboCompare,TRUE);

            if(hComboFont)EnableWindow(hComboFont,TRUE);

            if(hBtnResumo)EnableWindow(hBtnResumo,TRUE);
            if(hBtnVerResultado)EnableWindow(hBtnVerResultado,TRUE);
            if(hBtnRanking)EnableWindow(hBtnRanking,TRUE);

            HMENU hM2=GetSystemMenu(hwnd,FALSE);

            if(hM2)EnableMenuItem(hM2,SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);
        }

        AtualizarPainelPrincipal();

    }catch(const std::exception&e){
        MessageBoxW(hwnd,traducoes[langIndex].msgErroBenchmark,
        traducoes[langIndex].tituloErro,MB_ICONERROR);

        if(IsWindow(hwnd)){
            EnableWindow(hBtnRun,TRUE);
            EnableWindow(hComboLang,TRUE);
            EnableWindow(hComboCompare,TRUE);

            if(hComboFont)EnableWindow(hComboFont,TRUE);

            if(hBtnResumo)EnableWindow(hBtnResumo,TRUE);
            if(hBtnVerResultado)EnableWindow(hBtnVerResultado,TRUE);
            if(hBtnRanking)EnableWindow(hBtnRanking,TRUE);

            HMENU hM=GetSystemMenu(hwnd,FALSE);

            if(hM)EnableMenuItem(hM,SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);

            SetWindowTextW(hStaticStatus,traducoes[langIndex].statusErroBenchmark);
        }
    }catch(...){
        MessageBoxW(hwnd,traducoes[langIndex].msgErroDesconhecido,
        traducoes[langIndex].tituloErro,MB_ICONERROR);

        if(IsWindow(hwnd)){
            EnableWindow(hBtnRun,TRUE);
            EnableWindow(hComboLang,TRUE);
            EnableWindow(hComboCompare,TRUE);

            if(hComboFont)EnableWindow(hComboFont,TRUE);

            if(hBtnResumo)EnableWindow(hBtnResumo,TRUE);
            if(hBtnVerResultado)EnableWindow(hBtnVerResultado,TRUE);
            if(hBtnRanking)EnableWindow(hBtnRanking,TRUE);

            HMENU hM=GetSystemMenu(hwnd,FALSE);

            if(hM)EnableMenuItem(hM,SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);

            SetWindowTextW(hStaticStatus,traducoes[langIndex].statusErroBenchmark);
        }
    }

    benchmarkEmAndamento=false;
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        case WM_CREATE:{
            hMainWnd=hwnd;

            RECT wa;
            SystemParametersInfo(SPI_GETWORKAREA,0,&wa,0);

            int sw=wa.right-wa.left,sh=wa.bottom-wa.top;

            int ww=(1450<sw)?1450:sw;
            int wh=(910<sh)?910:sh;

            SetWindowPos(hwnd,NULL,0,0,ww,wh,SWP_NOZORDER);

            g_winW=ww;
            g_winH=wh;

            hStaticLang=CreateWindowW(L"STATIC",L"Idioma:",WS_VISIBLE|WS_CHILD,15,15,60,25,hwnd,(HMENU)ID_STATIC_LANG,NULL,NULL);

            hComboLang=CreateWindowW(L"COMBOBOX",L"",WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,80,15,150,250,hwnd,(HMENU)ID_COMBO_LANG,NULL,NULL);

            hStaticFont=NULL;
            hComboFont=NULL;

            hStaticCompare=CreateWindowW(L"STATIC",L"Comparar:",WS_CHILD,15,15,70,25,hwnd,(HMENU)ID_STATIC_COMPARE,NULL,NULL);

            hComboCompare=CreateWindowW(L"COMBOBOX",L"",WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,15,15,280,250,hwnd,(HMENU)ID_COMBO_PC_COMPARE,NULL,NULL);

            hStaticCpuA=CreateWindowW(L"STATIC",L"CPU A:",WS_VISIBLE|WS_CHILD,15,15,60,25,hwnd,(HMENU)ID_STATIC_CPU_A,NULL,NULL);

            hComboCpuA=CreateWindowW(L"COMBOBOX",L"",WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,15,15,220,250,hwnd,(HMENU)ID_COMBO_CPU_A,NULL,NULL);

            hStaticCpuB=CreateWindowW(L"STATIC",L"CPU B:",WS_VISIBLE|WS_CHILD,15,15,60,25,hwnd,(HMENU)ID_STATIC_CPU_B,NULL,NULL);

            hComboCpuB=CreateWindowW(L"COMBOBOX",L"",WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,15,15,220,250,hwnd,(HMENU)ID_COMBO_CPU_B,NULL,NULL);

            hBtnRun=CreateWindowW(L"BUTTON",L"Iniciar",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,90,30,hwnd,(HMENU)ID_BTN_RUN,NULL,NULL);

            hBtnResumo=CreateWindowW(L"BUTTON",L"\x26A1 RESUMO",WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_RESUMO,NULL,NULL);

            hBtnVerResultado=CreateWindowW(L"BUTTON",L"\x26A1 VER RESULTADO",WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_VER_RESULTADO,NULL,NULL);

            hBtnRanking=CreateWindowW(L"BUTTON",L"\x2605 RANKING",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_RANKING,NULL,NULL);

            hStaticStatus=CreateWindowW(L"STATIC",L"Pronto.",WS_VISIBLE|WS_CHILD,15,55,ww-30,25,hwnd,(HMENU)ID_STATIC_STATUS,NULL,NULL);

            hEditLog=CreateWindowW(L"RICHEDIT50W",L"",
                WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY|WS_VSCROLL|WS_HSCROLL,
                15,85,ww-30,wh-100,hwnd,(HMENU)ID_EDIT_LOG,NULL,NULL);

            SendMessageW(hEditLog,EM_EXLIMITTEXT,0,(LPARAM)(1024*1024));
            SendMessageW(hEditLog,EM_SETBKGNDCOLOR,0,RGB(255,255,255));
            SendMessageW(hEditLog,EM_SETTARGETDEVICE,(WPARAM)NULL,0);

            CHARFORMAT2W cf={0};
            cf.cbSize=sizeof(cf);

            cf.dwMask=CFM_SIZE|CFM_FACE|CFM_COLOR|CFM_WEIGHT;
            cf.yHeight=21*10;
            cf.wWeight=FW_MEDIUM;

            wcscpy_s(cf.szFaceName,L"Consolas");

            cf.crTextColor=RGB(0,0,0);
            cf.dwEffects=0;

            SendMessageW(hEditLog,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&cf);

#ifdef _WIN64
            g_oldEditLogProc=(WNDPROC)SetWindowLongPtrW(hEditLog,GWLP_WNDPROC,(LONG_PTR)EditLogProc);
#else
            g_oldEditLogProc=(WNDPROC)SetWindowLongW(hEditLog,GWL_WNDPROC,(LONG)EditLogProc);
#endif

            AtualizarFontesSimples(21);

            const wchar_t*langs[]={
                L"Portugues (Brasil)",L"English (US)",L"Espanol",L"Frances",
                L"Alemao",L"Italiano",L"Chines",L"Russo",L"Coreano",L"Holandes",L"Polones",L"Japones"
            };

            for(int i=0;i<12;++i)
                SendMessageW(hComboLang,CB_ADDSTRING,0,(LPARAM)langs[i]);

            SendMessageW(hComboLang,CB_SETCURSEL,0,0);

            AtualizarIdiomaInterface(0);
            PosicionarControlesTopo();

            CarregarListaNuvem(hwnd);
            AtualizarListaComparacao();
            AtualizarPainelPrincipal();

            break;
        }

        case WM_SYSCOMMAND:
            if((wParam&0xFFF0)==SC_CLOSE){
                if(benchmarkEmAndamento){
                    MessageBoxW(hwnd,traducoes[currentLangIndex].msgAguardeFechar,
                    traducoes[currentLangIndex].tituloAguarde,MB_ICONWARNING);

                    return 0;
                }
            }

            return DefWindowProcW(hwnd,uMsg,wParam,lParam);

        case WM_CTLCOLORSTATIC:{
            HDC h=(HDC)wParam;

            SetTextColor(h,RGB(30,30,30));
            SetBkMode(h,TRANSPARENT);

            return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
        }

        case WM_NOTIFY:{
            NMHDR* pH=(NMHDR*)lParam;

            if(pH->hwndFrom==hEditLog&&pH->code==EN_MSGFILTER){
                MSGFILTER* pF=(MSGFILTER*)lParam;

                if(pF->msg==WM_MOUSEWHEEL||pF->msg==WM_VSCROLL||pF->msg==WM_KEYDOWN){
                    DefWindowProcW(hwnd,uMsg,wParam,lParam);

                    SCROLLINFO si={sizeof(si),SIF_POS};
                    GetScrollInfo(hEditLog,SB_VERT,&si);

                    if(si.nPos>0&&!g_cabecalhoAtual.empty()){
                        POINT pt={0,0};

                        LONG fv=(LONG)SendMessageW(hEditLog,EM_CHARFROMPOS,0,(LPARAM)&pt);
                        LONG li=(LONG)SendMessageW(hEditLog,EM_LINEFROMCHAR,fv,0);

                        int len=(int)SendMessageW(hEditLog,EM_LINELENGTH,(WPARAM)fv,0);

                        if(len>0){
                            std::wstring ltt(len,L'\0');
                            *((WORD*)&ltt[0])=(WORD)len;

                            SendMessageW(hEditLog,EM_GETLINE,li,(LPARAM)&ltt[0]);

                            if(ltt.find(traducoes[currentLangIndex].colTeste)==std::wstring::npos){
                                LONG cp2=(LONG)SendMessageW(hEditLog,EM_LINEINDEX,li,0);

                                SendMessageW(hEditLog,EM_SETSEL,cp2,cp2);

                                std::wstring it=g_cabecalhoAtual+
                                L"---------------------------------------------------------------------------------------------------------------------------\r\n";

                                SendMessageW(hEditLog,EM_REPLACESEL,FALSE,(LPARAM)it.c_str());
                                SendMessageW(hEditLog,EM_LINESCROLL,0,2);
                            }
                        }
                    }

                    return 0;
                }
            }

            break;
        }

        case WM_COMMAND:
            if(LOWORD(wParam)==ID_COMBO_LANG&&HIWORD(wParam)==CBN_SELCHANGE){
                int li=(int)SendMessageW(hComboLang,CB_GETCURSEL,0,0);

                if(li>=0&&li<12)
                    AtualizarIdiomaInterface(li);
            }
            else if(LOWORD(wParam)==ID_COMBO_PC_COMPARE&&HIWORD(wParam)==CBN_SELCHANGE){
                AtualizarPainelPrincipal();
            }
            else if(LOWORD(wParam)==ID_COMBO_CPU_A&&HIWORD(wParam)==CBN_SELCHANGE){
                AtualizarPainelPrincipal();
            }
            else if(LOWORD(wParam)==ID_COMBO_CPU_B&&HIWORD(wParam)==CBN_SELCHANGE){
                AtualizarPainelPrincipal();
            }
            else if(LOWORD(wParam)==ID_BTN_RUN&&HIWORD(wParam)==BN_CLICKED){
                int li=(int)SendMessageW(hComboLang,CB_GETCURSEL,0,0);

                if(li<0||li>=12)li=0;

                std::thread(ExecutarBenchmarkThread,hwnd,li).detach();
            }
            else if(LOWORD(wParam)==ID_BTN_RESUMO&&HIWORD(wParam)==BN_CLICKED){
                int iA=-1,iB=-1;

                ObterSelecaoCpuXCpu(iA,iB);

                if(iA>0&&iB>0&&iA!=iB)
                    AbrirModalResumo(iA,iB,false);
            }
            else if(LOWORD(wParam)==ID_BTN_VER_RESULTADO&&HIWORD(wParam)==BN_CLICKED){
                if(benchmarkRealizado){
                    int p=(int)SendMessageW(hComboCompare,CB_GETCURSEL,0,0);

                    if(p>=0){
                        int idx=(int)SendMessageW(hComboCompare,CB_GETITEMDATA,p,0);

                        if(idx>0)
                            AbrirModalResumo(0,idx,true);
                    }
                }
            }
            else if(LOWORD(wParam)==ID_BTN_RANKING&&HIWORD(wParam)==BN_CLICKED){
                AbrirRanking();
            }

            break;

        case WM_DESTROY:
            if(hFontAtual)
                DeleteObject(hFontAtual);

            DestruirFontesModal();
            DestruirFontesRanking();

            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR pCmdLine,int nCmdShow){
    LoadLibraryW(L"Msftedit.dll");

    const wchar_t CN[]=L"BenchmarkAppClass";

    WNDCLASSW wc={};

    wc.lpfnWndProc=WindowProc;
    wc.hInstance=hInstance;
    wc.lpszClassName=CN;
    wc.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);

    RegisterClassW(&wc);

    HWND hwnd=CreateWindowExW(
        0,
        CN,
        L"Benchmark Multi-Core C++",
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1450,
        910,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(hwnd==NULL)
        return 0;

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    MSG msg={};

    while(GetMessageW(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}