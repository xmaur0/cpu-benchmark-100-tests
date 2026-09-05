#include <windows.h>
#include <richedit.h>
#include <wininet.h>
#include <wincrypt.h>
#include <shlobj.h>
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
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "shell32.lib")

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
#define ID_BTN_EFICIENCIA 114
#define ID_CHK_FILTRAR_REPETIDAS 115
#define ID_BTN_CPU_SIMILAR 116
#define ID_BTN_CPU_SIMILAR_SINGLE 117
#define ID_BTN_CPU_SIMILAR_MULTI 118
#define ID_BTN_LIMPAR_CPU 119
#define ID_MODAL_BTN_CLOSE 301
#define ID_RANKING_BTN_CLOSE 401

const wchar_t* NPOINT_DOC_ID = L"your id npoint account";
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
const wchar_t* btnRanking; const wchar_t* btnEficiencia; const wchar_t* rankingTitulo; const wchar_t* rankingEficienciaTitulo; const wchar_t* rankingFechar;
const wchar_t* escalonamentoLabel;
const wchar_t* chkFiltrarRepetidas;
const wchar_t* btnCpuSimilar;
const wchar_t* btnCpuSimilarSingle;
const wchar_t* btnCpuSimilarMulti;
const wchar_t* btnLimparCpu;
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
{ L"Benchmark Multi-Core C++",L"Idioma:",L"Comparar com:",L"Fonte:",L"Iniciar Benchmark",L"Pronto.",L"Executando MULTI-CORE...",L"Executando SINGLE-CORE...",L"RESULTADO FINAL (100 TESTES)",L"Nucleos: ",L"Teste",L"Seu PC",L"Outro PC",L"Dif",L"Pts",L"Selecione uma CPU...",L"Execute o benchmark primeiro.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** SEU PC E MAIS RAPIDO (+",L"*** SEU PC E MAIS LENTO (",L"*** EMPATE TECNICO ***",L"*** SELECIONE UM PC PARA VER A COMPARACAO ***",L"Erro",L"Erro durante o benchmark.",L"Erro desconhecido.",L"Erro no benchmark.",L"Aguarde",L"Aguarde o termino antes de fechar.",L"CPU A:",L"CPU B:",L"\x26A1 RESUMO",L"\x26A1 VER RESULTADO",L"VS",L"E MAIS RAPIDO",L"FECHAR",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Ganhou:",L"testes",L"\x2605 RANKING",L"\x2699 EFICI\x00caNCIA",L"RANKING GLOBAL",L"CPUs MAIS EFICIENTES",L"FECHAR" ,L"ESCALONAMENTO (Multi/Nucleos vs Single)" ,L"Filtrar CPUs repetidas (mostrar so a de mais threads)" ,L"CPU MAIS SEMELHANTE" ,L"CPU MAIS SEMELHANTE (SINGLE-CORE)",L"CPU MAIS SEMELHANTE (MULTI-CORE)" ,L"LIMPAR" },
{ L"C++ Multi-Core Benchmark",L"Language:",L"Compare with:",L"Font:",L"Start Benchmark",L"Ready.",L"Running MULTI-CORE...",L"Running SINGLE-CORE...",L"FINAL SCORE (100 TESTS)",L"Cores: ",L"Test",L"Your PC",L"Other PC",L"Diff",L"Score",L"Select a CPU...",L"Run benchmark first.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** YOUR PC IS FASTER (+",L"*** YOUR PC IS SLOWER (",L"*** TECHNICAL TIE ***",L"*** SELECT A PC TO COMPARE ***",L"Error",L"Benchmark error.",L"Unknown error.",L"Benchmark error.",L"Wait",L"Wait for benchmark to finish.",L"CPU A:",L"CPU B:",L"\x26A1 SUMMARY",L"\x26A1 VIEW RESULT",L"VS",L"IS FASTER",L"CLOSE",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Won:",L"tests",L"\x2605 RANKING",L"\x2699 EFFICIENCY",L"GLOBAL RANKING",L"MOST EFFICIENT CPUS",L"CLOSE" ,L"SCALING (Multi/Cores vs Single)" ,L"Filter duplicate CPUs (show only the one with most threads)" ,L"MOST SIMILAR CPU" ,L"MOST SIMILAR CPU (SINGLE-CORE)",L"MOST SIMILAR CPU (MULTI-CORE)" ,L"CLEAR" },
{ L"Benchmark Multi-Core C++",L"Idioma:",L"Comparar con:",L"Fuente:",L"Iniciar",L"Listo.",L"Ejecutando MULTI-CORE...",L"Ejecutando SINGLE-CORE...",L"PUNTUACION FINAL",L"Nucleos: ",L"Prueba",L"Tu PC",L"Otro PC",L"Dif",L"Pts",L"Selecciona una CPU...",L"Ejecuta el benchmark primero.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** TU PC ES MAS RAPIDA (+",L"*** TU PC ES MAS LENTA (",L"*** EMPATE ***",L"*** SELECCIONA UN PC ***",L"Error",L"Error en benchmark.",L"Error desconocido.",L"Error.",L"Espera",L"Espera a que termine.",L"CPU A:",L"CPU B:",L"\x26A1 RESUMEN",L"\x26A1 VER RESULTADO",L"VS",L"ES MAS RAPIDA",L"CERRAR",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gano:",L"pruebas",L"\x2605 RANKING",L"\x2699 EFICIENCIA",L"RANKING GLOBAL",L"CPUs MAS EFICIENTES",L"CERRAR" ,L"ESCALADO (Multi/Nucleos vs Single)" ,L"Filtrar CPUs repetidas (mostrar solo la de mas threads)" ,L"CPU MAS PARECIDA" ,L"CPU MAS PARECIDA (SINGLE-CORE)",L"CPU MAS PARECIDA (MULTI-CORE)" ,L"LIMPIAR" },
{ L"Test C++ Multi-Core",L"Langue:",L"Comparer:",L"Police:",L"Demarrer",L"Pret.",L"Tests MULTI-CORE...",L"Tests SINGLE-CORE...",L"SCORE FINAL",L"Coeurs: ",L"Test",L"Votre PC",L"Autre PC",L"Diff",L"Score",L"Selectionnez une CPU...",L"Lancez le benchmark.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAL <<",L"*** VOTRE PC EST PLUS RAPIDE (+",L"*** VOTRE PC EST PLUS LENT (",L"*** EGALITE ***",L"*** SELECTIONNEZ UN PC ***",L"Erreur",L"Erreur benchmark.",L"Erreur inconnue.",L"Erreur.",L"Patientez",L"Attendez la fin du test.",L"CPU A :",L"CPU B :",L"\x26A1 RESUME",L"\x26A1 VOIR RESULTAT",L"VS",L"EST PLUS RAPIDE",L"FERMER",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gagne:",L"tests",L"\x2605 CLASSEMENT",L"\x2699 EFFICACIT\x00c9",L"CLASSEMENT GLOBAL",L"CPUs PLUS EFFICACES",L"FERMER" ,L"MISE A ECHELLE (Multi/Coeurs vs Single)" ,L"Filtrer les CPU en double (afficher seulement le plus de threads)" ,L"CPU LA PLUS PROCHE" ,L"CPU LA PLUS PROCHE (SINGLE-CORE)",L"CPU LA PLUS PROCHE (MULTI-CORE)" ,L"EFFACER" },
{ L"C++ Multi-Core Benchmark",L"Sprache:",L"Vergleichen:",L"Schrift:",L"Starten",L"Bereit.",L"MULTI-CORE Tests...",L"SINGLE-CORE Tests...",L"ERGEBNIS",L"Kerne: ",L"Test",L"Ihr PC",L"Anderer PC",L"Diff",L"Pkt",L"CPU waehlen...",L"Bitte zuerst starten.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> GESAMT <<",L"*** IHR PC IST SCHNELLER (+",L"*** IHR PC IST LANGSAMER (",L"*** UNENTSCHIEDEN ***",L"*** PC AUSWAEHLEN ***",L"Fehler",L"Benchmark-Fehler.",L"Unbekannter Fehler.",L"Fehler.",L"Warten",L"Warten bis fertig.",L"CPU A:",L"CPU B:",L"\x26A1 ZUSAMMENFASSUNG",L"\x26A1 ERGEBNIS ANZEIGEN",L"VS",L"IST SCHNELLER",L"SCHLIESSEN",L"MULTI-CORE",L"SINGLE-CORE",L"PKT",L"Gewonnen:",L"Tests",L"\x2605 RANGLISTE",L"\x2699 EFFIZIENZ",L"GLOBALE RANGLISTE",L"EFFIZIENTESTE CPUs",L"SCHLIESSEN" ,L"SKALIERUNG (Multi/Kerne vs Single)" ,L"Doppelte CPUs filtern (nur die mit den meisten Threads zeigen)" ,L"AEHNLICHSTE CPU" ,L"AEHNLICHSTE CPU (SINGLE-CORE)",L"AEHNLICHSTE CPU (MULTI-CORE)" ,L"LOESCHEN" },
{ L"Benchmark C++ Multi-Core",L"Lingua:",L"Confronta:",L"Font:",L"Avvia",L"Pronto.",L"Test MULTI-CORE...",L"Test SINGLE-CORE...",L"PUNTEGGIO FINALE",L"Core: ",L"Test",L"Tuo PC",L"Altro PC",L"Diff",L"Pts",L"Seleziona una CPU...",L"Esegui prima il test.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTALE <<",L"*** IL TUO PC E PIU VELOCE (+",L"*** IL TUO PC E PIU LENTO (",L"*** PAREGGIO ***",L"*** SELEZIONA UN PC ***",L"Errore",L"Errore benchmark.",L"Errore sconosciuto.",L"Errore.",L"Attendi",L"Attendi la fine.",L"CPU A:",L"CPU B:",L"\x26A1 RIEPILOGO",L"\x26A1 VEDI RISULTATO",L"VS",L"E PIU VELOCE",L"CHIUDI",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Vinto:",L"test",L"\x2605 CLASSIFICA",L"\x2699 EFFICIENZA",L"CLASSIFICA GLOBALE",L"CPU PIU EFFICIENTI",L"CHIUDI" ,L"SCALABILITA (Multi/Core vs Single)" ,L"Filtra CPU duplicate (mostra solo quella con piu thread)" ,L"CPU PIU SIMILE" ,L"CPU PIU SIMILE (SINGLE-CORE)",L"CPU PIU SIMILE (MULTI-CORE)" ,L"PULISCI" },
{ L"C++ Multi-Core Benchmark",L"Yan Yu:",L"Bi Jiao:",L"Zi Ti:",L"Kai Shi",L"Jiu Xu",L"MULTI-CORE...",L"SINGLE-CORE...",L"ZUI ZHONG DE FEN",L"He Xin: ",L"Ce Shi",L"Ni De PC",L"Qi Ta PC",L"Cha Yi",L"Fen",L"Xuan Ze CPU...",L"Qing Xian Yun Xing.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> ZONG JI <<",L"*** NI DE PC GENG KUAI (+",L"*** NI DE PC GENG MAN (",L"*** PING JU ***",L"*** XUAN ZE PC ***",L"Cuo Wu",L"Benchmark Cuo Wu.",L"Wei Zhi Cuo Wu.",L"Cuo Wu.",L"Deng Dai",L"Deng Dai Wan Cheng.",L"CPU A:",L"CPU B:",L"\x26A1 ZONG JIE",L"\x26A1 CHA KAN JIE GUO",L"VS",L"GENG KUAI",L"GUAN BI",L"MULTI-CORE",L"SINGLE-CORE",L"FEN",L"Ying:",L"ce shi",L"\x2605 PAI MING",L"\x2699 XIAO LU",L"QUAN QIU PAI MING",L"ZUI GAO XIAO CPU",L"GUAN BI" ,L"KUO ZHAN XING (Multi/He vs Single)" ,L"Guo Lu Zhong Fu CPU (Zhi Xian Shi Xian Cheng Zui Duo De)" ,L"ZUI XIANG SI DE CPU" ,L"ZUI XIANG SI DE CPU (SINGLE-CORE)",L"ZUI XIANG SI DE CPU (MULTI-CORE)" ,L"QING CHU" },
{ L"C++ Multi-Core Benchmark",L"Yazyk:",L"Sravnit:",L"Shrift:",L"Start",L"Gotov.",L"MULTI-CORE...",L"SINGLE-CORE...",L"ITOG",L"Yadra: ",L"Test",L"Vash PK",L"Drugoy PK",L"Razn",L"Pts",L"Vyberite CPU...",L"Snachala zapustite.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> ITOGO <<",L"*** VASH PK BYSTREE (+",L"*** VASH PK MEDLENNEE (",L"*** NICHYA ***",L"*** VYBERITE PK ***",L"Oshibka",L"Oshibka testa.",L"Neizvestnaya oshibka.",L"Oshibka.",L"Zhdite",L"Zhdite okonchaniya.",L"CPU A:",L"CPU B:",L"\x26A1 ITog",L"\x26A1 SMOTRET REZULTAT",L"VS",L"BYSTREE",L"ZAKRYT",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Vyigral:",L"testov",L"\x2605 REITING",L"\x2699 EFFEKTYVNOST",L"GLOBALNIY REITING",L"SAMYE EFFEKTYVNYE CPU",L"ZAKRYT" ,L"MASSHTABIROVANIE (Multi/Yadra vs Single)" ,L"Filtrovat povtoryayushchiesya CPU (tolko s bolshim chislom potokov)" ,L"SAMYY POKHOZHIY CPU" ,L"SAMYY POKHOZHIY CPU (SINGLE-CORE)",L"SAMYY POKHOZHIY CPU (MULTI-CORE)" ,L"OCHISTIT" },
{ L"C++ Multi-Core Benchmark",L"Eon Eo:",L"Bi Gyo:",L"Geul Ggol:",L"Si Jak",L"Jun Bi",L"MULTI-CORE...",L"SINGLE-CORE...",L"CHOE JONG JEOM SU",L"Ko Eo: ",L"Te Seuteu",L"Nae PC",L"Da Reun PC",L"Cha I",L"Jeom",L"CPU Seon Taek...",L"Meon Jeo Sil Haeng.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> HAB GYE <<",L"*** NAE PC GA DEO PPA REUM (+",L"*** NAE PC GA DEO NEU RIM (",L"*** MU SEUNG BU ***",L"*** PC SEON TAEK ***",L"O Ryu",L"Benchmark O Ryu.",L"Al Su Eom Neun O Ryu.",L"O Ryu.",L"Gi Da Rim",L"Gi Da Ryeo Ju Se Yo.",L"CPU A:",L"CPU B:",L"\x26A1 YO YAK",L"\x26A1 GYEOL GWA BO GI",L"VS",L"DEO PPA REUM",L"DA GT GI",L"MULTI-CORE",L"SINGLE-CORE",L"JEOM",L"I gim:",L"te seuteu",L"\x2605 SUN WI",L"\x2699 HYO YUL",L"JEON CHE SUN WI",L"GO HYO YUL CPU",L"DA GT GI" ,L"HWAK JANG SEONG (Multi/Koa vs Single)" ,L"Jung Bok CPU Pil Teo (Smajil Su Ga Ga Jang Manheun Geot Man)" ,L"GA JANG BI SEUT HAN CPU" ,L"GA JANG BI SEUT HAN CPU (SINGLE-CORE)",L"GA JANG BI SEUT HAN CPU (MULTI-CORE)" ,L"CHO GI HWA" },
{ L"C++ Multi-Core Benchmark",L"Taal:",L"Vergelijk:",L"Lettertype:",L"Start",L"Klaar.",L"MULTI-CORE...",L"SINGLE-CORE...",L"RESULTAAT",L"Kernen: ",L"Test",L"Jouw PC",L"Andere PC",L"Verschil",L"Score",L"Selecteer CPU...",L"Voer eerst uit.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> TOTAAL <<",L"*** JOUW PC IS SNELLER (+",L"*** JOUW PC IS LANGZAMER (",L"*** GELIJKSPEL ***",L"*** SELECTEER PC ***",L"Fout",L"Benchmark fout.",L"Onbekende fout.",L"Fout.",L"Wacht",L"Wacht tot voltooid.",L"CPU A:",L"CPU B:",L"\x26A1 SAMENVATTING",L"\x26A1 BEKIJK RESULTAAT",L"VS",L"IS SNELLER",L"SLUITEN",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Gewonnen:",L"tests",L"\x2605 RANGSCHIKKING",L"\x2699 EFFICI\x00cbNTIE",L"GLOBALE RANGSCHIKKING",L"MEEST EFFICI\x00cbNTE CPUs",L"SLUITEN" ,L"SCHAALBAARHEID (Multi/Cores vs Single)" ,L"Dubbele CPUs filteren (alleen die met de meeste threads tonen)" ,L"MEEST GELIJKENDE CPU" ,L"MEEST GELIJKENDE CPU (SINGLE-CORE)",L"MEEST GELIJKENDE CPU (MULTI-CORE)" ,L"WISSEN" },
{ L"Benchmark C++ Multi-Core",L"Jezyk:",L"Porownaj:",L"Czcionka:",L"Start",L"Gotowy.",L"MULTI-CORE...",L"SINGLE-CORE...",L"WYNIK",L"Rdzenie: ",L"Test",L"Twoj PC",L"Inny PC",L"Roznica",L"Wynik",L"Wybierz CPU...",L"Najpierw uruchom.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> RAZEM <<",L"*** TWOJ PC SZYBSZY (+",L"*** TWOJ PC WOLNIEJSZY (",L"*** REMIS ***",L"*** WYBIERZ PC ***",L"Blad",L"Blad testu.",L"Nieznany blad.",L"Blad.",L"Czekaj",L"Czekaj na koniec.",L"CPU A:",L"CPU B:",L"\x26A1 PODSUMOWANIE",L"\x26A1 ZOBACZ WYNIK",L"VS",L"SZYBSZY",L"ZAMKNIJ",L"MULTI-CORE",L"SINGLE-CORE",L"PKT",L"Wygrane:",L"testy",L"\x2605 RANKING",L"\x2699 WYDAJNO\x015a\x0106",L"RANKING GLOBALNY",L"NAJBARDZIEJ WYDAJNE CPU",L"ZAMKNIJ" ,L"SKALOWALNOSC (Multi/Rdzenie vs Single)" ,L"Filtruj powielone CPU (pokaz tylko z najwieksza liczba watkow)" ,L"NAJBARDZIEJ PODOBNY CPU" ,L"NAJBARDZIEJ PODOBNY CPU (SINGLE-CORE)",L"NAJBARDZIEJ PODOBNY CPU (MULTI-CORE)" ,L"WYCZYSC" },
{ L"C++ Multi-Core Benchmark",L"Nihongo:",L"Hikaku:",L"Font:",L"Kaishi",L"Junbi",L"MULTI-CORE...",L"SINGLE-CORE...",L"SAISHUU SUKOA",L"Koa: ",L"Tesuto",L"Anata PC",L"Hoka PC",L"Sai",L"Sukoa",L"CPU Sentaku...",L"Saisho Ni Jikkou.",L"[MULTI-CORE]",L"[SINGLE-CORE]",L">> GOUKEI <<",L"*** ANATA PC HAYAI (+",L"*** ANATA PC OSOI (",L"*** HIKIWAKE ***",L"*** PC SENTAKU ***",L"Era",L"Benchmark Era.",L"Fumei Era.",L"Era.",L"Machi",L"Shuuryou Wo Machi.",L"CPU A:",L"CPU B:",L"\x26A1 MATOME",L"\x26A1 KEKKA WO MIRU",L"VS",L"HAYAI",L"ToJiRu",L"MULTI-CORE",L"SINGLE-CORE",L"PTS",L"Kachi:",L"tesuto",L"\x2605 RANKINGU",L"\x2699 KOURITSU",L"SEKAI RANKINGU",L"SAIKOU KOURITSU CPU",L"ToJiRu" ,L"SUKEIRINGU (Multi/Koa vs Single)" ,L"Juufuku CPU Firuta (Sureddo Suu Ga Saidai No Mono Nomi Hyouji)" ,L"MOTTOMO NITEIRU CPU" ,L"MOTTOMO NITEIRU CPU (SINGLE-CORE)",L"MOTTOMO NITEIRU CPU (MULTI-CORE)" ,L"KURIA" }
};

HWND hEditLog=NULL,hBtnRun=NULL,hComboLang=NULL,hComboCompare=NULL,hComboFont=NULL;
HWND hStaticLang=NULL,hStaticCompare=NULL,hStaticStatus=NULL,hStaticFont=NULL,hMainWnd=NULL;
HWND hStaticCpuA=NULL,hComboCpuA=NULL,hStaticCpuB=NULL,hComboCpuB=NULL;
HWND hBtnResumo=NULL,hBtnVerResultado=NULL,hBtnRanking=NULL,hBtnEficiencia=NULL;
HWND hChkFiltrarRepetidas=NULL;
HWND hBtnCpuSimilar=NULL;
HWND hBtnCpuSimilarSingle=NULL,hBtnCpuSimilarMulti=NULL;
HWND hBtnLimparCpu=NULL;
HWND hModalWnd=NULL,hRankingWnd=NULL,hEficienciaWnd=NULL;
int g_eficScroll=0;

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
{ L"Selecione uma CPU...",{0},{0},0.0,0.0,0 }
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
void AbrirEficiencia();
void FecharEficiencia();
void DesenharEficiencia(HDC hdc,RECT&rc);
LRESULT CALLBACK EficienciaProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void CalcularEficienciaRanking(std::vector<double>& eficienciaPorPc, size_t& liderIdx);
void DesenharRanking(HDC hdc,RECT& rc);
LRESULT CALLBACK RankingProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK EditLogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
int MedirTextoLargura(HFONT fonte,const wchar_t* texto);
void ObterSelecaoCpuXCpu(int&idxA,int&idxB);
int EncontrarCpuMaisSemelhante(const double scoresMultiAlvo[100],const double scoresSingleAlvo[100],int idxExcluir);
int EncontrarCpuMaisProxima(const double scoresMultiAlvo[100],const double scoresSingleAlvo[100],int idxExcluir,bool usarMulti,bool usarSingle);
void ExecutarBuscaCpuSimilar(bool usarMulti,bool usarSingle);
void VerificarBotaoCpuSimilar();
void CriarFontesRanking();
void DestruirFontesRanking();
void CriarFontesModal();
void DestruirFontesModal();

// === Sincronizacao local <-> nuvem (cache local criptografado) ===
void MesclarDadosNaMemoria(const std::string& jn);
std::string GerarJsonCompleto();
std::string BaixarJsonNuvem();
bool EnviarJsonParaNuvem(const std::string& jd);
bool SalvarJsonLocalCriptografado(const std::string& json);
std::string CarregarJsonLocalCriptografado();
int ContarRegistrosJson(const std::string& jn);
void SincronizarDadosInicializacao(HWND hwnd);

std::wstring Utf8ToWstring(const std::string& str){if(str.empty())return L"";int s=MultiByteToWideChar(CP_UTF8,0,&str[0],(int)str.size(),NULL,0);std::wstring w(s,0);MultiByteToWideChar(CP_UTF8,0,&str[0],(int)str.size(),&w[0],s);return w;}
std::string WstringToUtf8(const std::wstring& wstr){if(wstr.empty())return"";int s=WideCharToMultiByte(CP_UTF8,0,&wstr[0],(int)wstr.size(),NULL,0,NULL,NULL);std::string str(s,0);WideCharToMultiByte(CP_UTF8,0,&wstr[0],(int)wstr.size(),&str[0],s,NULL,NULL);return str;}

std::wstring ObterNomeCompletoCPU(){HKEY hKey;wchar_t buffer[256]=L"CPU Desconhecido";DWORD bs=sizeof(buffer);if(RegOpenKeyExW(HKEY_LOCAL_MACHINE,L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",0,KEY_READ,&hKey)==ERROR_SUCCESS){RegQueryValueExW(hKey,L"ProcessorNameString",NULL,NULL,(LPBYTE)buffer,&bs);RegCloseKey(hKey);}std::wstring nome(buffer);size_t lc=nome.find_last_not_of(L"\r\n\t ");if(lc!=std::wstring::npos)nome.erase(lc+1);return nome;}

// Declaracoes antecipadas (sistema de comparacao por razao + media geometrica,
// substitui o antigo esquema baseado em log10 + soma de pontos)
double IndiceGeometricoRelativo(const double scoresAlvo[100],const double scoresRef[100]);
double TotalBrutoSoma(const double scores[100]);
double TotalBrutoSomaVector(const std::vector<double>& scores);

// === JSON BLINDADO ===
std::string GerarJsonCompleto(){std::string json="{\"data\":[";bool p=true;for(size_t i=1;i<pcsCadastrados.size();++i){if(!p)json+=",";p=false;std::wstring ne=pcsCadastrados[i].nome;size_t pos=0;while((pos=ne.find(L'"',pos))!=std::wstring::npos){ne.replace(pos,1,L"\\\"");pos+=2;}json+="{\"nome\":\""+WstringToUtf8(ne)+"\",\"totalMulti\":"+std::to_string(TotalBrutoSoma(pcsCadastrados[i].scoresMultiCore))+",\"totalSingle\":"+std::to_string(TotalBrutoSoma(pcsCadastrados[i].scoresSingleCore))+",\"threads\":"+std::to_string(pcsCadastrados[i].numThreads)+",\"scoresMulti\":[";for(int j=0;j<100;++j){json+=std::to_string(pcsCadastrados[i].scoresMultiCore[j]);if(j<99)json+=",";}json+="],\"scoresSingle\":[";for(int j=0;j<100;++j){json+=std::to_string(pcsCadastrados[i].scoresSingleCore[j]);if(j<99)json+=",";}json+="]}";}json+="]}";return json;}

// Baixa o JSON da nuvem. IMPORTANTE: so retorna "" quando REALMENTE nao
// conseguiu falar com o servidor (sem internet, DNS falhou, timeout, etc).
// Se o servidor respondeu com sucesso (HTTP 200) mas o conteudo veio vazio ou
// sem o campo "data" (ex: documento foi limpo/apagado pela pagina do npoint),
// isso NAO conta como falha de conexao — retorna a string tal como veio
// (mesmo vazia), pra quem chamou saber que HOUVE resposta do servidor.
bool g_ultimaConexaoNuvemOk=false;
std::string BaixarJsonNuvem(){
    g_ultimaConexaoNuvemOk=false;
    std::string r;
    HINTERNET hI=InternetOpenW(L"BenchmarkAppClient",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    if(!hI)return"";
    std::wstring url=GetNpointUrl();
    HINTERNET hF=InternetOpenUrlW(hI,url.c_str(),NULL,0,INTERNET_FLAG_RELOAD|INTERNET_FLAG_SECURE|INTERNET_FLAG_NO_CACHE_WRITE,0);
    if(hF){
        DWORD statusCode=0,scSize=sizeof(statusCode),idx=0;
        bool statusOk=HttpQueryInfoW(hF,HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER,&statusCode,&scSize,&idx)!=0;
        char buf[8192];DWORD br=0;
        while(InternetReadFile(hF,buf,sizeof(buf)-1,&br)&&br>0){buf[br]='\0';r+=buf;}
        InternetCloseHandle(hF);
        // Se nao deu pra ler o status HTTP, mantem o comportamento antigo (so
        // considera ok se veio algum corpo). Se leu o status, exige 200 OK.
        g_ultimaConexaoNuvemOk = statusOk ? (statusCode==200) : !r.empty();
    }
    InternetCloseHandle(hI);
    return r;
}

// =============================================================================
// CACHE LOCAL CRIPTOGRAFADO (DPAPI) + SINCRONIZACAO COM A NUVEM
// =============================================================================
// Usamos CryptProtectData/CryptUnprotectData (DPAPI), API nativa do Windows:
// - o conteudo fica ilegivel para quem abrir o arquivo num editor de texto;
// - qualquer bit alterado no arquivo faz o CryptUnprotectData FALHAR (o Windows
//   verifica integridade internamente), entao adulteracao == arquivo tratado
//   como corrompido/inexistente, nunca como dado valido;
// - so a mesma conta de usuario, na mesma maquina, consegue descriptografar.
// Entropia adicional amarra o arquivo especificamente a este app.
static const BYTE g_entropiaLocal[16]={0x4B,0x39,0xA1,0x7C,0xE2,0x05,0x88,0xF1,0x3D,0x6A,0x91,0xBB,0x2C,0x40,0x77,0x1E};


// =============================================================================
// ISOLAMENTO DE CACHE POR VERSÃO DO EXECUTÁVEL
// =============================================================================
std::wstring ObterHashDoExecutavel() {
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);

    HANDLE hFile = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return L"unknown_version";

    DWORD size = GetFileSize(hFile, NULL);
    std::vector<BYTE> buf(size);
    DWORD read = 0;
    ReadFile(hFile, buf.data(), size, &read, NULL);
    CloseHandle(hFile);

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) return L"unknown_version";
    
    std::wstring result = L"unknown_version";
    if (CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        if (CryptHashData(hHash, buf.data(), read, 0)) {
            BYTE hash[32];
            DWORD hashLen = 32;
            if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
                wchar_t hex[65] = {0};
                for (DWORD i = 0; i < hashLen; i++) swprintf_s(hex + i * 2, 3, L"%02x", hash[i]);
                result = std::wstring(hex).substr(0, 16); 
            }
        }
        CryptDestroyHash(hHash);
    }
    CryptReleaseContext(hProv, 0);
    return result;
}

std::wstring GetLocalDataDir(){
    wchar_t path[MAX_PATH];
    if(SHGetFolderPathW(NULL,CSIDL_LOCAL_APPDATA,NULL,0,path)!=S_OK)return L".";
    std::wstring dir=std::wstring(path)+L"\\BenchmarkApp";
    CreateDirectoryW(dir.c_str(),NULL);
    return dir;
}
std::wstring GetLocalCachePath(){
    static std::wstring cachedPath;
    if (!cachedPath.empty()) return cachedPath;
    std::wstring hash = ObterHashDoExecutavel();
    cachedPath = GetLocalDataDir() + L"\\cache_" + hash + L".dat";
    return cachedPath;
}

bool SalvarJsonLocalCriptografado(const std::string& json){
    if(json.empty()||json=="{\"data\":[]}")return false;
    DATA_BLOB dataIn{};dataIn.pbData=(BYTE*)json.data();dataIn.cbData=(DWORD)json.size();
    // ENTROPIA DINÂMICA: Combina a entropia base com o hash do executável
    std::wstring verHash = ObterHashDoExecutavel();
    std::vector<BYTE> entropyBytes(sizeof(g_entropiaLocal) + verHash.size() * sizeof(wchar_t));
    memcpy(entropyBytes.data(), g_entropiaLocal, sizeof(g_entropiaLocal));
    memcpy(entropyBytes.data() + sizeof(g_entropiaLocal), verHash.c_str(), verHash.size() * sizeof(wchar_t));
    DATA_BLOB entropy{}; entropy.pbData = entropyBytes.data(); entropy.cbData = (DWORD)entropyBytes.size();
    DATA_BLOB dataOut{};
    if(!CryptProtectData(&dataIn,L"BenchmarkAppCache",&entropy,NULL,NULL,CRYPTPROTECT_UI_FORBIDDEN,&dataOut))return false;
    // Escreve em arquivo temporario e so troca pelo definitivo se a escrita for
    // completa (evita corromper o cache se o programa fechar no meio da gravacao).
    std::wstring destino=GetLocalCachePath();
    std::wstring tmp=destino+L".tmp";
    bool ok=false;
    HANDLE hFile=CreateFileW(tmp.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile!=INVALID_HANDLE_VALUE){
        DWORD written=0;
        ok=WriteFile(hFile,dataOut.pbData,dataOut.cbData,&written,NULL)&&written==dataOut.cbData;
        FlushFileBuffers(hFile);
        CloseHandle(hFile);
    }
    LocalFree(dataOut.pbData);
    if(ok){
        DeleteFileW(destino.c_str());
        ok=MoveFileW(tmp.c_str(),destino.c_str())!=0;
    } else {
        DeleteFileW(tmp.c_str());
    }
    return ok;
}

std::string CarregarJsonLocalCriptografado(){
    HANDLE hFile=CreateFileW(GetLocalCachePath().c_str(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)return"";
    DWORD size=GetFileSize(hFile,NULL);
    if(size==0||size==INVALID_FILE_SIZE){CloseHandle(hFile);return"";}
    std::vector<BYTE> buf(size);
    DWORD readBytes=0;
    BOOL rok=ReadFile(hFile,buf.data(),size,&readBytes,NULL);
    CloseHandle(hFile);
    if(!rok||readBytes!=size)return"";
    DATA_BLOB dataIn{};dataIn.pbData=buf.data();dataIn.cbData=size;
    // ENTROPIA DINÂMICA: Combina a entropia base com o hash do executável
    std::wstring verHash = ObterHashDoExecutavel();
    std::vector<BYTE> entropyBytes(sizeof(g_entropiaLocal) + verHash.size() * sizeof(wchar_t));
    memcpy(entropyBytes.data(), g_entropiaLocal, sizeof(g_entropiaLocal));
    memcpy(entropyBytes.data() + sizeof(g_entropiaLocal), verHash.c_str(), verHash.size() * sizeof(wchar_t));
    DATA_BLOB entropy{}; entropy.pbData = entropyBytes.data(); entropy.cbData = (DWORD)entropyBytes.size();
    DATA_BLOB dataOut{};
    // Se o arquivo foi adulterado, veio de outra maquina/usuario, ou esta
    // corrompido, a descriptografia falha aqui -> tratamos como "sem cache local".
    if(!CryptUnprotectData(&dataIn,NULL,&entropy,NULL,NULL,CRYPTPROTECT_UI_FORBIDDEN,&dataOut))return"";
    std::string json((char*)dataOut.pbData,dataOut.cbData);
    LocalFree(dataOut.pbData);
    return json;
}

int ContarRegistrosJson(const std::string& jn) {
    if (jn.empty()) return 0;
    if (jn.find("{\"data\":[") == std::string::npos) return 0;

    // BLINDAGEM: um JSON completo gerado por este app SEMPRE termina com "]}"
    // (fecha o array "data" e o objeto raiz — ver GerarJsonCompleto). Se o
    // conteudo foi truncado/corrompido no meio (rede caiu, editor da nuvem
    // cortou o texto, etc), o final nao vai ser exatamente esse — mesmo que
    // um array interno tenha fechado normalmente antes do corte. Cortamos
    // espacos/quebras de linha do final (a nuvem pode devolver isso) antes
    // de comparar.
    size_t fim = jn.find_last_not_of(" \t\r\n");
    if (fim == std::string::npos || fim < 1) return 0;
    if (!(jn[fim] == '}' && jn[fim - 1] == ']')) return 0;

    // BLINDAGEM 2: balanceamento de chaves/colchetes. Cobre truncamentos no
    // MEIO do documento (nao so no final) — ex: rede caiu bem no meio de um
    // numero, mas por coincidencia algum "]}" sobrou depois no texto residual.
    int chaves = 0, colchetes = 0;
    for (char c : jn) {
        if (c == '{') chaves++;
        else if (c == '}') chaves--;
        else if (c == '[') colchetes++;
        else if (c == ']') colchetes--;
    }
    if (chaves != 0 || colchetes != 0) return 0;

    int count = 0; size_t p = 0;
    while ((p = jn.find("{\"nome\"", p)) != std::string::npos) { count++; p += 7; }
    return count;
}

std::vector<double> ExtrairArrayDouble(const std::string& json,size_t sp){std::vector<double> r;size_t p=json.find('[',sp);if(p==std::string::npos)return r;p++;while(p<json.size()){while(p<json.size()&&(json[p]==' '||json[p]=='\t'||json[p]=='\n'||json[p]=='\r'))p++;if(p>=json.size()||json[p]==']')break;size_t ns=p;while(p<json.size()&&json[p]!=','&&json[p]!=']')p++;if(p>ns){try{r.push_back(std::stod(json.substr(ns,p-ns)));}catch(...){}}if(p<json.size()&&json[p]==',')p++;}
// BLINDAGEM: um array de scores valido gerado por este app tem SEMPRE
// exatamente 100 elementos (ver GerarJsonCompleto). Qualquer coisa diferente
// disso e sinal de corrupcao/truncamento nao pega pelas blindagens de
// ContarRegistrosJson (ex: um numero cortado no meio, uma virgula a mais/a
// menos). Rejeita retornando vazio, que MesclarDadosNaMemoria ja trata como
// "sem atualizacao" (nao aplica dado parcial por cima de um resultado valido).
if(r.size()!=100)return std::vector<double>();
return r;}

void MesclarDadosNaMemoria(const std::string& jn){size_t pa=jn.find("\"data\":[");if(pa==std::string::npos)return;size_t p=pa+7;while((p=jn.find("{\"nome\"",p))!=std::string::npos){size_t eo=jn.find("}",p);if(eo==std::string::npos)break;size_t sn=jn.find(":\"",p)+2,en=jn.find("\"",sn);if(sn==std::string::npos||en==std::string::npos||en>eo){p++;continue;}std::wstring wn=Utf8ToWstring(jn.substr(sn,en-sn));double tm=0,ts=0;int th=0;size_t ptm=jn.find("\"totalMulti\":",en);if(ptm!=std::string::npos&&ptm<eo)try{tm=std::stod(jn.substr(ptm+13));}catch(...){}size_t pts2=jn.find("\"totalSingle\":",en);if(pts2!=std::string::npos&&pts2<eo)try{ts=std::stod(jn.substr(pts2+14));}catch(...){}size_t pth=jn.find("\"threads\":",en);if(pth!=std::string::npos&&pth<eo)try{th=std::stoi(jn.substr(pth+10));}catch(...){}auto smv=ExtrairArrayDouble(jn,en);size_t pefa=jn.find(']',en);std::vector<double> ssv;if(pefa!=std::string::npos&&pefa<eo)ssv=ExtrairArrayDouble(jn,pefa);bool ex=false;for(size_t k=1;k<pcsCadastrados.size();++k){if(pcsCadastrados[k].nome==wn){ex=true;bool at=false;double novoMultiVis=TotalBrutoSomaVector(smv);
double atualMultiVis=TotalBrutoSoma(pcsCadastrados[k].scoresMultiCore);
if(!smv.empty()&&novoMultiVis>atualMultiVis){pcsCadastrados[k].totalMultiCore=novoMultiVis;for(int s=0;s<100&&s<(int)smv.size();++s)pcsCadastrados[k].scoresMultiCore[s]=smv[s];at=true;}double novoSingleVis=TotalBrutoSomaVector(ssv);
double atualSingleVis=TotalBrutoSoma(pcsCadastrados[k].scoresSingleCore);
if(!ssv.empty()&&novoSingleVis>atualSingleVis){pcsCadastrados[k].totalSingleCore=novoSingleVis;for(int s=0;s<100&&s<(int)ssv.size();++s)pcsCadastrados[k].scoresSingleCore[s]=ssv[s];at=true;}if(at&&th>0)pcsCadastrados[k].numThreads=th;break;}}if(!ex){PCReferencia nv;nv.nome=wn;nv.totalMultiCore=TotalBrutoSomaVector(smv);nv.totalSingleCore=TotalBrutoSomaVector(ssv);nv.numThreads=th;for(int s=0;s<100;++s){nv.scoresMultiCore[s]=(s<(int)smv.size())?smv[s]:0.0;nv.scoresSingleCore[s]=(s<(int)ssv.size())?ssv[s]:0.0;}pcsCadastrados.push_back(nv);}p=eo+1;}}

// Envia um JSON ja pronto (string) para a nuvem via POST. Extraido do antigo
// SalvarListaNuvemNativo para poder ser reaproveitado pela sincronizacao de
// inicializacao sem duplicar o codigo de rede.
bool EnviarJsonParaNuvem(const std::string& jd){
    if(jd=="{\"data\":[]}"||jd.length()<20)return false;
    HINTERNET hs=InternetOpenW(L"BenchmarkClient",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    if(!hs)return false;
    HINTERNET hc=InternetConnectW(hs,L"api.npoint.io",INTERNET_DEFAULT_HTTPS_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
    if(!hc){InternetCloseHandle(hs);return false;}
    std::wstring path=GetNpointPath();
    HINTERNET hr=HttpOpenRequestW(hc,L"POST",path.c_str(),NULL,NULL,NULL,INTERNET_FLAG_SECURE|INTERNET_FLAG_RELOAD,0);
    if(!hr){InternetCloseHandle(hc);InternetCloseHandle(hs);return false;}
    std::wstring hdrs=L"Content-Type: application/json\r\nAccept: */*\r\n";
    BOOL ev=HttpSendRequestW(hr,hdrs.c_str(),(DWORD)hdrs.size(),(LPVOID)jd.c_str(),(DWORD)jd.size());
    InternetCloseHandle(hr);InternetCloseHandle(hc);InternetCloseHandle(hs);
    return ev==TRUE;
}

// Chamada apos rodar um benchmark novo: tenta mesclar com o que ja esta na
// nuvem e enviar, mas o CACHE LOCAL e sempre atualizado com o resultado novo
// independente de ter internet ou nao — assim um benchmark rodado offline
// nunca se perde (fica salvo local e sobe pra nuvem na proxima sincronizacao
// com internet, seja no proximo envio ou na proxima abertura do programa).
bool SalvarListaNuvemNativo(){
    std::string jd=GerarJsonCompleto();

    std::string jan=BaixarJsonNuvem();
    bool nuvemOk=g_ultimaConexaoNuvemOk;

    if(nuvemOk&&!jan.empty()){
        MesclarDadosNaMemoria(jan);
        jd=GerarJsonCompleto(); // regera incluindo o que a nuvem tinha e o local ainda nao tinha
    }

    // Salva local SEMPRE, com ou sem internet — resultado novo nunca fica so
    // em memoria (RAM) esperando o programa fechar e sumir.
    SalvarJsonLocalCriptografado(jd);

    if(!nuvemOk)return false; // sem internet: fica so salvo local, tenta de novo depois

    return EnviarJsonParaNuvem(jd);
}

// =============================================================================
// SINCRONIZACAO DE INICIALIZACAO (local criptografado <-> nuvem)
// =============================================================================
// IMPORTANTE sobre "nao perder dados": a mesclagem real e SEMPRE feita por
// CONTEUDO (nome do PC, via MesclarDadosNaMemoria), nunca so pela quantidade
// de registros. Se a comparacao fosse feita so pela quantidade, dois arquivos
// com a MESMA quantidade de registros mas PCs diferentes fariam o app achar
// que "esta tudo igual" e um dos lados seria perdido silenciosamente. Por
// isso: local e nuvem sao SEMPRE mesclados em memoria (uniao dos dois,
// mantendo sempre o maior resultado de cada PC — dedup, nunca duplica CPU).
// A CONTAGEM (nuvem < local / == / >) e usada so para decidir a ACAO de rede
// (enviar pra nuvem, ou nao), como pedido — nunca para decidir o que entra ou
// nao na mesclagem.
void SincronizarDadosInicializacao(HWND hwnd){
    // LIMPEZA AUTOMÁTICA: Remove caches de versões anteriores do executável
    {
        std::wstring dir = GetLocalDataDir();
        std::wstring currentCache = GetLocalCachePath();
        WIN32_FIND_DATAW fd;
        HANDLE hFind = FindFirstFileW((dir + L"\\cache_*.dat").c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                std::wstring fullPath = dir + L"\\" + fd.cFileName;
                if (_wcsicmp(fullPath.c_str(), currentCache.c_str()) != 0) {
                    DeleteFileW(fullPath.c_str());
                }
            } while (FindNextFileW(hFind, &fd));
            FindClose(hFind);
        }
    }

    std::string jsonLocal=CarregarJsonLocalCriptografado();
    std::string jsonNuvem=BaixarJsonNuvem();
    bool nuvemOk=g_ultimaConexaoNuvemOk; // conectou de verdade no servidor (HTTP 200), mesmo que vazio

    int nLocal=ContarRegistrosJson(jsonLocal);
    int nNuvem=nuvemOk?ContarRegistrosJson(jsonNuvem):-1; // 0 se conectou mas doc veio vazio/zerado; -1 se nem conectou

    // Uniao completa em memoria (isso e o que garante zero perda de dados).
    if(!jsonLocal.empty())MesclarDadosNaMemoria(jsonLocal);
    if(nuvemOk&&!jsonNuvem.empty())MesclarDadosNaMemoria(jsonNuvem);

    if(!nuvemOk){
        // Sem internet / nuvem fora do ar: segue so com o cache local, sem
        // tentar enviar nada (evita sobrescrever a nuvem com dado incompleto).
        return;
    }

    std::string jsonMesclado=GerarJsonCompleto();

    if(nNuvem<nLocal){
        // Nuvem tem menos registros que o local -> local "leva vantagem":
        // envia o resultado mesclado (local+nuvem) pra nuvem.
        EnviarJsonParaNuvem(jsonMesclado);
        SalvarJsonLocalCriptografado(jsonMesclado);
    } else if(nNuvem>nLocal){
        // Nuvem tem mais registros -> nao envia nada, so atualiza o cache
        // local com o resultado mesclado (que ja contem o que a nuvem tinha).
        SalvarJsonLocalCriptografado(jsonMesclado);
    } else {
        // Mesma quantidade -> nao mexe na nuvem. Ainda assim grava o merge no
        // cache local (idempotente: se o conteudo for identico, e uma
        // re-gravacao inofensiva; se havia diferenca de conteudo com mesma
        // contagem, o merge acima ja garantiu que nada foi perdido em memoria).
        SalvarJsonLocalCriptografado(jsonMesclado);
    }
}

double calcularScoreNormalizado(long long tOps,double tSeg,double fEsc){if(tSeg<=0)return 0;return((double)tOps/tSeg/fEsc)/100.0;}

// =============================================================================
// HELPERS: COMPARACAO POR RAZAO + MEDIA GEOMETRICA (sem log10 / sem pontos artificiais)
// =============================================================================
// Calcula o indice geometrico agregado entre dois conjuntos de 100 scores BRUTOS
// (sem nenhuma transformacao): indice = media_geometrica(alvo_i / referencia_i)
// para todo teste i em que ambos os valores sao validos (>0, nao-NaN).
//
// Por que media geometrica e nao aritmetica: a razao entre dois testes e sempre
// assimetrica em escala (ex: 2x mais rapido num teste e 0.5x = 2x mais lento
// noutro deveriam se cancelar, resultando em empate). A media geometrica
// preserva essa simetria; a aritmetica nao (fica enviesada pelo teste com a
// maior razao absoluta). Usamos soma de logaritmos e exponenciamos no final
// para nao estourar double multiplicando 100 razoes diretamente.
double IndiceGeometricoRelativo(const double scoresAlvo[100],const double scoresRef[100]){
    double somaLog=0.0;
    int n=0;

    for(int i=0;i<100;++i){
        double v=scoresAlvo[i];
        double r=scoresRef[i];

        if(v>0.0&&r>0.0&&v==v&&r==r){
            somaLog+=std::log(v/r);
            ++n;
        }
    }

    if(n==0)return 1.0;

    return std::exp(somaLog/(double)n);
}

// Eficiencia de escalonamento: quanto cada nucleo entrega, RODANDO EM GRUPO,
// como percentual do que ele entrega SOZINHO (single-core). Diferente da
// Eficiencia (que compara contra outras CPUs), esta compara a CPU contra ela
// mesma — isola o efeito de paralelismo (contencao de cache/memoria, limite
// de power do pacote, throttling termico) sem misturar com "quao rapido e o
// nucleo em si" (isso o single-core ja mede sozinho).
// 100% = escala perfeito. Bem abaixo disso = sofre contencao ao usar todos os
// nucleos ao mesmo tempo.
double CalcularEscalonamento(double totalMulti,double totalSingle,int threads){
    if(threads<=0||totalSingle<=0.0||totalMulti<0.0)return 0.0;
    return (totalMulti/(double)threads)/totalSingle*100.0;
}

// Extrai o nome BASE da CPU, removendo o sufixo " (N Threads)" que o app
// sempre adiciona ao registrar (ver linha de registro do benchmark). Se o
// sufixo nao bater no formato esperado, devolve o nome completo sem alterar
// (protege contra remover pedaco errado de um nome que nao segue o padrao).
std::wstring NomeBaseCPU(const std::wstring&nomeCompleto){
    const std::wstring suf=L" Threads)";
    if(nomeCompleto.size()<suf.size())return nomeCompleto;
    if(nomeCompleto.compare(nomeCompleto.size()-suf.size(),suf.size(),suf)!=0)return nomeCompleto;

    size_t buscaAte=nomeCompleto.size()-suf.size();
    size_t p=nomeCompleto.rfind(L" (",buscaAte);
    if(p==std::wstring::npos)return nomeCompleto;

    size_t numStart=p+2;
    if(buscaAte<=numStart)return nomeCompleto;

    for(size_t i=numStart;i<buscaAte;++i)
        if(!iswdigit(nomeCompleto[i]))return nomeCompleto;

    return nomeCompleto.substr(0,p);
}

bool g_filtrarCpusRepetidas=false;

// Retorna os indices (1..pcsCadastrados.size()-1) que devem aparecer nas
// telas (combos, Ranking Global, Eficiencia). Com o filtro ligado, agrupa por
// nome BASE da CPU e mantem so a entrada com MAIS threads de cada grupo —
// filtro PURAMENTE DE EXIBICAO: pcsCadastrados e o JSON continuam com todos
// os registros normalmente, sincronizacao/merge nao sao afetados.
std::vector<size_t> ObterIndicesFiltrados(){
    std::vector<size_t> todos;
    for(size_t i=1;i<pcsCadastrados.size();++i)
        todos.push_back(i);

    if(!g_filtrarCpusRepetidas)return todos;

    std::unordered_map<std::wstring,size_t> melhorPorNomeBase;
    for(size_t i:todos){
        std::wstring base=NomeBaseCPU(pcsCadastrados[i].nome);
        auto it=melhorPorNomeBase.find(base);
        if(it==melhorPorNomeBase.end()||pcsCadastrados[i].numThreads>pcsCadastrados[it->second].numThreads)
            melhorPorNomeBase[base]=i;
    }

    std::vector<size_t> filtrados;
    filtrados.reserve(melhorPorNomeBase.size());
    for(auto&par:melhorPorNomeBase)
        filtrados.push_back(par.second);

    return filtrados;
}

// Soma simples dos scores brutos (sem log10, sem peso). Usado apenas como
// indicador interno de "esse resultado e mais novo/melhor que o ja salvo" ao
// mesclar dados da nuvem — nunca exibido diretamente ao usuario como pontuacao.
// Varre a lista inteira de CPUs cadastradas (respeitando o filtro de
// duplicadas, se ligado) e devolve o indice (em pcsCadastrados) da CPU cuja
// combinacao de scores mais se aproxima dos scores-alvo informados.
// usarMulti/usarSingle controlam QUAIS metricas entram na conta:
//  - as duas ligadas -> "mais semelhante" geral (single + multi juntos).
//  - so usarSingle -> "mais proxima em SINGLE-CORE" (multi e ignorado).
//  - so usarMulti -> "mais proxima em MULTI-CORE" (single e ignorado).
// idxExcluir e ignorado na busca (nunca pode ser devolvido) — usado para
// nao deixar a CPU se "encontrar" quando ela mesma e a origem da
// comparacao. A "distancia" usa a mesma media geometrica de razoes ja usada
// no resto do app (IndiceGeometricoRelativo): quanto mais perto de 1.0 for a
// razao (em log), mais parecida e a CPU. Quando as duas metricas estao
// ligadas, somamos as duas distancias pra pesar igualmente. Devolve -1 se
// nao encontrar nenhuma CPU valida (lista vazia ou so a excluida).
int EncontrarCpuMaisProxima(const double scoresMultiAlvo[100],const double scoresSingleAlvo[100],int idxExcluir,bool usarMulti,bool usarSingle){
    std::vector<size_t> idxs=ObterIndicesFiltrados();

    int melhorIdx=-1;
    double melhorDist=1e300;

    for(size_t i:idxs){
        if((int)i==idxExcluir)continue;

        double dist=0.0;
        bool valido=true;

        if(usarMulti){
            double idxMulti=IndiceGeometricoRelativo(pcsCadastrados[i].scoresMultiCore,scoresMultiAlvo);

            if(idxMulti<=0.0)valido=false;
            else dist+=std::fabs(std::log(idxMulti));
        }

        if(valido&&usarSingle){
            double idxSingle=IndiceGeometricoRelativo(pcsCadastrados[i].scoresSingleCore,scoresSingleAlvo);

            if(idxSingle<=0.0)valido=false;
            else dist+=std::fabs(std::log(idxSingle));
        }

        if(!valido)continue;

        if(dist<melhorDist){
            melhorDist=dist;
            melhorIdx=(int)i;
        }
    }

    return melhorIdx;
}

// Mantido por compatibilidade/clareza: "mais semelhante" = considera as
// duas metricas (single-core E multi-core) juntas.
int EncontrarCpuMaisSemelhante(const double scoresMultiAlvo[100],const double scoresSingleAlvo[100],int idxExcluir){
    return EncontrarCpuMaisProxima(scoresMultiAlvo,scoresSingleAlvo,idxExcluir,true,true);
}

double TotalBrutoSoma(const double scores[100]){
    double total=0.0;
    for(int i=0;i<100;++i)total+=scores[i];
    return total;
}

double TotalBrutoSomaVector(const std::vector<double>& scores){
    double total=0.0;
    for(int i=0;i<100;++i){
        double v=(i<(int)scores.size())?scores[i]:0.0;
        total+=v;
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

// Formata "quantas vezes mais rapido" com 1 casa decimal, virgula (padrao
// BR). Ex.: 5.6 -> "5,6". Usado nas telas de comparacao e no modal Resumo,
// sempre derivado do MESMO indice geometrico que ja gera a % de diferenca —
// entao "Xx" e "%" nunca podem se contradizer entre si.
std::wstring FormatarVezes(double valor){
    if(valor!=valor||valor<1.0)valor=1.0;
    wchar_t buf[32];
    swprintf_s(buf,L"%.1f",valor);
    for(wchar_t*p=buf;*p;++p)if(*p==L'.')*p=L',';
    return buf;
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

// Le de volta o texto exatamente como o RichEdit tem armazenado internamente
// — necessario porque EM_SETSEL usa a contagem de caracteres INTERNA do
// controle, que pode nao bater 1:1 com o std::wstring original usado pra
// montar o texto (RichEdit pode tratar quebras de linha de forma diferente).
std::wstring LerTextoRichEdit(HWND h){
    int len=GetWindowTextLengthW(h);
    if(len<=0)return L"";
    std::vector<wchar_t> buf((size_t)len+1);
    GetWindowTextW(h,buf.data(),len+1);
    return std::wstring(buf.data());
}

// Colore (mantendo o negrito que AplicarLinhaTotalMaior ja aplicou na linha
// TOTAL) a PRIMEIRA ocorrencia de cada substring de "alvos", buscando sempre
// a partir de onde a busca anterior parou — garante pegar a ocorrencia certa
// em ordem, mesmo se o mesmo texto aparecer mais de uma vez no documento.
// Busca no texto REAL do controle (ver LerTextoRichEdit), nao no wstring
// usado pra montar o texto. Deve ser chamada DEPOIS de FormatarLogComparacao().
void ColorirSubstringsEmOrdem(HWND h,const std::vector<std::wstring>&alvos,COLORREF cor){
    if(!h||alvos.empty())return;
    std::wstring texto=LerTextoRichEdit(h);
    if(texto.empty())return;

    DWORD selS=0,selE=0;SendMessageW(h,EM_GETSEL,(WPARAM)&selS,(LPARAM)&selE);
    SendMessageW(h,WM_SETREDRAW,FALSE,0);
    SendMessageW(h,EM_SETREADONLY,FALSE,0);

    CHARFORMAT2W cf={0};cf.cbSize=sizeof(cf);
    cf.dwMask=CFM_COLOR|CFM_BOLD;
    cf.dwEffects=CFE_BOLD;
    cf.crTextColor=cor;

    size_t cursor=0;
    for(const auto&alvo:alvos){
        if(alvo.empty())continue;
        size_t p=texto.find(alvo,cursor);
        if(p==std::wstring::npos)continue;
        SendMessageW(h,EM_SETSEL,(WPARAM)p,(LPARAM)(p+alvo.size()));
        SendMessageW(h,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)&cf);
        cursor=p+alvo.size();
    }

    SendMessageW(h,EM_SETREADONLY,TRUE,0);
    SendMessageW(h,EM_SETSEL,selS,selE);
    SendMessageW(h,WM_SETREDRAW,TRUE,0);
    InvalidateRect(h,NULL,TRUE);
}

void AplicarCoresVencedoras(const std::vector<std::wstring>&alvos){
    ColorirSubstringsEmOrdem(hEditLog,alvos,RGB(0,150,0));
}

void AplicarCoresPerdedoras(const std::vector<std::wstring>&alvos){
    ColorirSubstringsEmOrdem(hEditLog,alvos,RGB(200,0,0));
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

    const double*scA,*scB;
    std::wstring nA,nB;

    if(meuPcVsOutro){
        nA=ObterNomeCompletoCPU()+L" ("+std::to_wstring(meuUltimoNumThreads)+L" Threads)";
        nB=pcsCadastrados[idxB].nome;

        scA=isMulti?meuUltimoScoreTestsMulti:meuUltimoScoreTestsSingle;
        scB=isMulti?pcsCadastrados[idxB].scoresMultiCore:pcsCadastrados[idxB].scoresSingleCore;
    }else{
        nA=pcsCadastrados[idxA].nome;
        nB=pcsCadastrados[idxB].nome;

        scA=isMulti?pcsCadastrados[idxA].scoresMultiCore:pcsCadastrados[idxA].scoresSingleCore;
        scB=isMulti?pcsCadastrados[idxB].scoresMultiCore:pcsCadastrados[idxB].scoresSingleCore;
    }

    // Sistema perfeito: media geometrica das razoes teste-a-teste (B/A), sem
    // nenhuma transformacao (log10) e sem somar "pontos" de escalas diferentes.
    double idxBA=IndiceGeometricoRelativo(scB,scA);

    bool bVence=(idxBA>=1.0);

    std::wstring nV,nP;
    const double*scV,*scP;

    if(bVence){
        nV=nB; nP=nA; scV=scB; scP=scA;
    }else{
        nV=nA; nP=nB; scV=scA; scP=scB;
    }

    // Indice do vencedor sempre >=1 (quantas vezes mais rapido ele e). "diff"
    // e a mesma leitura simples usada nas tabelas: quanto o vencedor supera o
    // perdedor, relativo ao PERDEDOR (pode passar de 100% em diferencas
    // grandes) — bate exatamente com o "Dif" do painel comparativo e do
    // CPU x CPU pro mesmo par de PCs.
    double idxVencedor=bVence?idxBA:(1.0/idxBA);
    if(idxVencedor<1.0)idxVencedor=1.0;

    double diff=(idxVencedor-1.0)*100.0;

    int gV=0,gP=0;

    for(int i=0;i<100;++i){
        double vv=scV[i];
        double vp=scP[i];

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

    // "Xx MAIS RAPIDO": mesmo idxVencedor que ja gera o "+X%" ali em cima,
    // entao os dois numeros (% e Xx) nunca podem contradizer um ao outro.
    wchar_t msgVezes[128];
    std::wstring vezesModalFmt=FormatarVezes(idxVencedor);
    swprintf_s(msgVezes,L"%sx %s",vezesModalFmt.c_str(),t.modalMaisRapido);

    DrawTextW(hdc,msgVezes,-1,&r,DT_CENTER|DT_SINGLELINE);
    y+=34;

    // Barra proporcional ao indice do vencedor: normalizada de forma assintotica
    // (idx/(idx+1)), sempre entre 50% e 100% do comprimento — nao depende mais de
    // somas de escalas diferentes, entao nunca estoura nem fica "vazia" a toa.
    double rat=idxVencedor/(idxVencedor+1.0);

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

// Pontuacao maxima do ranking: o 1o lugar SEMPRE fica em 100% / RANKING_MAX_PONTOS,
// e todo mundo abaixo dele e proporcional a essa referencia. Nada de somas em
// escalas diferentes nem "bilhoes de pontos" — o teto e sempre este valor.
const double RANKING_MAX_PONTOS=1000.0;

// Calcula o indice geometrico de cada PC cadastrado (indices 1..N) em relacao a
// uma ancora fixa (o primeiro PC cadastrado). Qualquer PC serve de ancora — o
// resultado de comparar dois PCs quaisquer entre si nao muda com a escolha,
// entao a ordenacao final do ranking e sempre correta independente de quem
// acabou virando a ancora.
void CalcularIndicesGeometricosRanking(bool isMulti,std::vector<double>&idxPorPc){
    idxPorPc.assign(pcsCadastrados.size(),0.0);

    if(pcsCadastrados.size()<=1)return;

    size_t ancora=1;
    const double*ref=isMulti?pcsCadastrados[ancora].scoresMultiCore:pcsCadastrados[ancora].scoresSingleCore;

    for(size_t i=1;i<pcsCadastrados.size();++i){
        const double*v=isMulti?pcsCadastrados[i].scoresMultiCore:pcsCadastrados[i].scoresSingleCore;
        idxPorPc[i]=IndiceGeometricoRelativo(v,ref);
    }
}

void DesenharColunaRanking(HDC hdc,int colLeft,int colRight,int topY,int bottomY,
std::vector<size_t>&indices,std::vector<double>&idxGeoPorPc,double liderIdx,bool isMulti,int scrollOffset,
const wchar_t* headerOverride=nullptr){
    const IdiomaTextos&t=traducoes[currentLangIndex];

    COLORREF corH=isMulti?RGB(0,220,255):RGB(255,165,0);
    COLORREF corBr=isMulti?RGB(0,200,230):RGB(255,140,0);

    int lineH=38,headerH=35;

    SetBkMode(hdc,TRANSPARENT);

    HFONT of=(HFONT)SelectObject(hdc,hFontRankHeader);

    SetTextColor(hdc,corH);
    RECT rh={colLeft,topY,colRight,topY+headerH};
    DrawTextW(hdc,headerOverride?headerOverride:(isMulti?t.modalMultiCore:t.modalSingleCore),-1,&rh,DT_CENTER|DT_SINGLELINE);

    HPEN hp=CreatePen(PS_SOLID,2,corH);
    HPEN op=(HPEN)SelectObject(hdc,hp);

    MoveToEx(hdc,colLeft+10,topY+headerH-2,NULL);
    LineTo(hdc,colRight-10,topY+headerH-2);

    SelectObject(hdc,op);
    DeleteObject(hp);

    int listTop=topY+headerH+5;
    int maxLines=(bottomY-listTop)/lineH;

    if(maxLines<1)maxLines=1;

    if(liderIdx<=0.0)liderIdx=1.0;

    int startIdx=scrollOffset;
    int endIdx=startIdx+maxLines;

    if(endIdx>(int)indices.size())endIdx=(int)indices.size();

    for(int i=startIdx;i<endIdx;i++){
        int rank=i+1;
        size_t idx=indices[i];

        // Percentual sempre normalizado pelo lider: lider = sempre 100.0%.
        double perc=(idxGeoPorPc[idx]/liderIdx)*100.0;
        double pontos=(perc/100.0)*RANKING_MAX_PONTOS;

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
        std::wstring pontosFmt=FormatarNumero2Decimais(pontos);
        swprintf_s(scStr,L"%s PTS (%.1f%%)",pontosFmt.c_str(),perc);

        int scW=170;

        RECT rsc={colRight-scW-5,ly+2,colRight-5,ly+18};
        DrawTextW(hdc,scStr,-1,&rsc,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

        double ratio=perc/100.0;
        if(ratio>1.0)ratio=1.0;
        if(ratio<0.0)ratio=0.0;

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

    std::vector<size_t>idxM=ObterIndicesFiltrados();
    std::vector<size_t>idxS=idxM;

    // Indice geometrico de CADA pc cadastrado vs a ancora fixa (calculado uma
    // vez so, reaproveitado tanto pra ordenar quanto pra desenhar as barras).
    std::vector<double> idxGeoMulti,idxGeoSingle;
    CalcularIndicesGeometricosRanking(true,idxGeoMulti);
    CalcularIndicesGeometricosRanking(false,idxGeoSingle);

    std::sort(idxM.begin(),idxM.end(),[&](size_t a,size_t b){
        return idxGeoMulti[a]>idxGeoMulti[b];
    });

    std::sort(idxS.begin(),idxS.end(),[&](size_t a,size_t b){
        return idxGeoSingle[a]>idxGeoSingle[b];
    });

    double liderM=idxM.empty()?1.0:idxGeoMulti[idxM[0]];
    double liderS=idxS.empty()?1.0:idxGeoSingle[idxS[0]];

    DesenharColunaRanking(hdc,10,midX-5,60,rc.bottom-70,idxM,idxGeoMulti,liderM,true,g_rankScrollMulti);
    DesenharColunaRanking(hdc,midX+5,rc.right-10,60,rc.bottom-70,idxS,idxGeoSingle,liderS,false,g_rankScrollSingle);
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


// =============================================================================
// RANKING DE EFICIÊNCIA (Score Multi-Thread / Threads)
// =============================================================================
// =============================================================================
// RANKING DE EFICIÊNCIA (Índice Geométrico Normalizado por Thread)
// CORRIGIDO: Remove soma aritmética de pontos brutos. Usa média geométrica
// relativa a uma âncora, dividida pelo número de threads, para medir a
// qualidade real da arquitetura (IPC) independente da escala dos testes.
// =============================================================================
void CalcularEficienciaRanking(std::vector<double>& eficienciaPorPc, size_t& liderIdx) {
    eficienciaPorPc.assign(pcsCadastrados.size(), 0.0);
    liderIdx = 0;
    if (pcsCadastrados.size() <= 1) return;

    // 1. Define âncora (primeiro PC válido com threads > 0) para base da média geométrica
    size_t ancoraIdx = 0;
    for (size_t k = 1; k < pcsCadastrados.size(); ++k) {
        if (pcsCadastrados[k].numThreads > 0) {
            ancoraIdx = k;
            break;
        }
    }
    
    // Se não encontrou nenhuma âncora válida, não há como calcular
    if (ancoraIdx == 0 || pcsCadastrados[ancoraIdx].numThreads <= 0) return;

    const double* refMulti = pcsCadastrados[ancoraIdx].scoresMultiCore;
    double maxEficiencia = 0.0;

    // 2. Calcula eficiência bruta: IndiceGeometrico / Threads
    for (size_t i = 1; i < pcsCadastrados.size(); ++i) {
        int threads = pcsCadastrados[i].numThreads;
        if (threads <= 0) continue;

        // Usa a mesma função do Modal/Ranking Global: média geométrica das razões teste-a-teste
        double idxGeo = IndiceGeometricoRelativo(pcsCadastrados[i].scoresMultiCore, refMulti);
        
        double eficiencia = idxGeo / (double)threads;
        
        eficienciaPorPc[i] = eficiencia; // Armazena temporariamente o valor bruto
        if (eficiencia > maxEficiencia) {
            maxEficiencia = eficiencia;
            liderIdx = i;
        }
    }

    // 3. Normaliza para porcentagem (Líder = 100%) para exibição na barra de progresso
    if (maxEficiencia > 0.0) {
        for (size_t i = 1; i < pcsCadastrados.size(); ++i) {
            if (pcsCadastrados[i].numThreads > 0 && eficienciaPorPc[i] > 0.0) {
                eficienciaPorPc[i] = (eficienciaPorPc[i] / maxEficiencia) * 100.0;
            } else {
                eficienciaPorPc[i] = 0.0;
            }
        }
    }
}

void DesenharEficiencia(HDC hdc, RECT& rc) {
    const IdiomaTextos& t = traducoes[currentLangIndex];
    HBRUSH hb = CreateSolidBrush(RGB(10, 15, 30)); FillRect(hdc, &rc, hb); DeleteObject(hb);
    HPEN hp = CreatePen(PS_SOLID, 2, RGB(0, 220, 180));
    HPEN op = (HPEN)SelectObject(hdc, hp);
    HBRUSH hn = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH ob = (HBRUSH)SelectObject(hdc, hn);
    Rectangle(hdc, 1, 1, rc.right - 1, rc.bottom - 1);
    SelectObject(hdc, op); SelectObject(hdc, ob); DeleteObject(hp);
    SetBkMode(hdc, TRANSPARENT);
    HFONT of = (HFONT)SelectObject(hdc, hFontRankTitulo);
    SetTextColor(hdc, RGB(0, 255, 200));
    RECT rt = { 10, 10, rc.right - 10, 55 };
    DrawTextW(hdc, t.rankingEficienciaTitulo, -1, &rt, DT_CENTER | DT_SINGLELINE);
    SelectObject(hdc, of);
    std::vector<double> eficienciaPorPc; size_t liderIdx = 0;
    CalcularEficienciaRanking(eficienciaPorPc, liderIdx);
    std::vector<size_t> idxEfic=ObterIndicesFiltrados();
    idxEfic.erase(std::remove_if(idxEfic.begin(),idxEfic.end(),
        [](size_t i){return pcsCadastrados[i].numThreads<=0;}),idxEfic.end());
    std::sort(idxEfic.begin(), idxEfic.end(), [&](size_t a, size_t b) { return eficienciaPorPc[a] > eficienciaPorPc[b]; });

    // O lider (100%) tem que ser sempre quem esta no TOPO da lista EXIBIDA —
    // se nao, com o filtro de CPUs repetidas ligado, o verdadeiro maior valor
    // global poderia estar numa entrada filtrada/escondida, e o topo da lista
    // exibida nunca bateria 100% (mesmo problema ja resolvido no Ranking
    // Global, que recalcula o lider depois de ordenar a lista exibida).
    double liderExibido=idxEfic.empty()?100.0:eficienciaPorPc[idxEfic[0]];
    if(liderExibido<=0.0)liderExibido=100.0;

    DesenharColunaRanking(hdc, 10, rc.right - 10, 60, rc.bottom - 70, idxEfic, eficienciaPorPc, liderExibido, true, g_eficScroll, t.rankingEficienciaTitulo);
}

LRESULT CALLBACK EficienciaProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_ERASEBKGND: { HDC h=(HDC)wParam; RECT rc; GetClientRect(hwnd,&rc); HBRUSH hb=CreateSolidBrush(RGB(10,15,30)); FillRect(h,&rc,hb); DeleteObject(hb); return 1; }
    case WM_PAINT: { PAINTSTRUCT ps; HDC hdc=BeginPaint(hwnd,&ps); HDC hm=CreateCompatibleDC(hdc); RECT rc; GetClientRect(hwnd,&rc); HBITMAP hbm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom); HBITMAP obm=(HBITMAP)SelectObject(hm,hbm); DesenharEficiencia(hm,rc); BitBlt(hdc,0,0,rc.right,rc.bottom,hm,0,0,SRCCOPY); SelectObject(hm,obm); DeleteObject(hbm); DeleteDC(hm); EndPaint(hwnd,&ps); return 0; }
    case WM_MOUSEWHEEL: { int delta=GET_WHEEL_DELTA_WPARAM(wParam); int maxS=(int)pcsCadastrados.size()-1-10; if(maxS<0)maxS=0; g_eficScroll-=(delta>0)?3:-3; if(g_eficScroll<0)g_eficScroll=0; if(g_eficScroll>maxS)g_eficScroll=maxS; InvalidateRect(hwnd,NULL,TRUE); return 0; }
    case WM_COMMAND: if(LOWORD(wParam)==ID_RANKING_BTN_CLOSE) FecharEficiencia(); break;
    case WM_CLOSE: FecharEficiencia(); return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void AbrirEficiencia() {
    if (hEficienciaWnd) return;
    g_eficScroll = 0; CriarFontesRanking();
    int rw=800, rh=750, sw=GetSystemMetrics(SM_CXSCREEN), sh=GetSystemMetrics(SM_CYSCREEN);
    int px=(sw-rw)/2, py=(sh-rh)/2; if(px<0)px=0; if(py<0)py=0;
    WNDCLASSW wc={}; wc.lpfnWndProc=EficienciaProc; wc.hInstance=GetModuleHandle(NULL);
    wc.lpszClassName=L"EficienciaClass"; wc.hCursor=LoadCursor(NULL,IDC_ARROW); wc.hbrBackground=NULL;
    RegisterClassW(&wc);
    hEficienciaWnd=CreateWindowExW(WS_EX_TOOLWINDOW,L"EficienciaClass",L"",WS_POPUP|WS_VISIBLE,px,py,rw,rh,hMainWnd,NULL,GetModuleHandle(NULL),NULL);
    HWND hbc=CreateWindowW(L"BUTTON",traducoes[currentLangIndex].rankingFechar,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,(rw-180)/2,rh-60,180,48,hEficienciaWnd,(HMENU)ID_RANKING_BTN_CLOSE,GetModuleHandle(NULL),NULL);
    SendMessageW(hbc,WM_SETFONT,(WPARAM)hFontRankBtn,TRUE);
    ShowWindow(hEficienciaWnd,SW_SHOW); UpdateWindow(hEficienciaWnd);
}

void FecharEficiencia() { if(hEficienciaWnd){DestroyWindow(hEficienciaWnd);hEficienciaWnd=NULL;} }

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

    VerificarBotaoCpuSimilar();
}

// Os tres botoes de "CPU parecida" (geral, single-core, multi-core) tem o
// MESMO criterio de habilitar/desabilitar — o que muda entre eles e so qual
// metrica entra na busca quando clicados. Ver ExecutarBuscaCpuSimilar.
//
//  1) Comparacao CPU A x CPU B: se exatamente UM dos dois combos (CPU A ou
//     CPU B) tiver uma CPU especifica selecionada e o OUTRO ainda estiver em
//     "Selecione..." -> botoes habilitam. Ao clicar, preenche o campo vazio
//     com a CPU mais proxima da que ja foi escolhida. Se os DOIS ja
//     estiverem preenchidos, essa funcao nao faz sentido -> os botoes ficam
//     desabilitados (nao ha "campo vazio" pra completar).
//
//  2) Resultado do benchmark: se o benchmark do usuario ja rodou -> botoes
//     tambem habilitam. Ao clicar (sem CPU A/B configurando o caso 1
//     acima), busca na lista a CPU mais proxima do RESULTADO do usuario e
//     seleciona ela no combo "Comparar com:".
void VerificarBotaoCpuSimilar(){
    int idxA=-1,idxB=-1;
    ObterSelecaoCpuXCpu(idxA,idxB);

    bool selA=(idxA>0);
    bool selB=(idxB>0);

    bool habilitar=false;

    // Caso 2: benchmark do usuario ja rodou.
    if(benchmarkRealizado)habilitar=true;

    // Caso 1: exatamente um dos dois combos CPU A/CPU B preenchido.
    if(selA!=selB)habilitar=true;

    // Se os DOIS combos CPU A/CPU B estiverem preenchidos, nao ha campo
    // vazio pra completar nesse contexto -> forca desabilitado, mesmo que
    // o benchmark do usuario ja tenha rodado.
    if(selA&&selB)habilitar=false;

    if(hBtnCpuSimilar)EnableWindow(hBtnCpuSimilar,habilitar?TRUE:FALSE);
    if(hBtnCpuSimilarSingle)EnableWindow(hBtnCpuSimilarSingle,habilitar?TRUE:FALSE);
    if(hBtnCpuSimilarMulti)EnableWindow(hBtnCpuSimilarMulti,habilitar?TRUE:FALSE);
}

// Executa a busca de "CPU mais proxima" e aplica o resultado na tela.
// usarMulti/usarSingle escolhem a metrica (repassados pra
// EncontrarCpuMaisProxima): os dois ligados = "geral", so um ligado =
// busca so por aquela metrica. Regra de prioridade e a mesma dos 3 botoes:
// se exatamente 1 dos combos CPU A/CPU B estiver preenchido, completa o
// outro; senao, se o benchmark do usuario ja rodou, usa o resultado dele e
// seleciona a CPU mais proxima no combo "Comparar com:".
void ExecutarBuscaCpuSimilar(bool usarMulti,bool usarSingle){
    int idxA=-1,idxB=-1;

    ObterSelecaoCpuXCpu(idxA,idxB);

    bool selA=(idxA>0);
    bool selB=(idxB>0);

    if(selA!=selB){
        int idxRef=selA?idxA:idxB;
        HWND comboAlvo=selA?hComboCpuB:hComboCpuA;

        int melhor=EncontrarCpuMaisProxima(pcsCadastrados[idxRef].scoresMultiCore,pcsCadastrados[idxRef].scoresSingleCore,idxRef,usarMulti,usarSingle);

        if(melhor>0&&comboAlvo){
            int total=(int)SendMessageW(comboAlvo,CB_GETCOUNT,0,0);

            for(int i=0;i<total;++i){
                int d=(int)SendMessageW(comboAlvo,CB_GETITEMDATA,i,0);

                if(d==melhor){
                    SendMessageW(comboAlvo,CB_SETCURSEL,i,0);
                    break;
                }
            }

            AtualizarPainelPrincipal();
        }
    }else if(benchmarkRealizado){
        int melhor=EncontrarCpuMaisProxima(meuUltimoScoreTestsMulti,meuUltimoScoreTestsSingle,-1,usarMulti,usarSingle);

        if(melhor>0&&hComboCompare){
            int total=(int)SendMessageW(hComboCompare,CB_GETCOUNT,0,0);

            for(int i=0;i<total;++i){
                int d=(int)SendMessageW(hComboCompare,CB_GETITEMDATA,i,0);

                if(d==melhor){
                    SendMessageW(hComboCompare,CB_SETCURSEL,i,0);
                    break;
                }
            }

            AtualizarPainelPrincipal();
        }
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

    // Botao "Limpar" (desmarca CPU A e CPU B, volta ambos pra
    // "Selecione uma CPU..."). Fica logo depois do combo CPU B, na mesma
    // linha (ou quebra pra proxima se nao couber, igual os combos acima).
    {
        int wLimpar=MedirTextoLargura(hFontAtual,traducoes[currentLangIndex].btnLimparCpu)+(int)(30*esc);
        if(wLimpar<(int)(90*esc))wLimpar=(int)(90*esc);

        if(x+wLimpar>lim&&x>15){
            x=15;
            y+=aL;
        }

        if(hBtnLimparCpu)MoveWindow(hBtnLimparCpu,x,y,wLimpar,aB2,TRUE);

        x+=wLimpar+eC;
    }

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
int xRanking=x;
x+=wBR+eC;
if(hBtnEficiencia)MoveWindow(hBtnEficiencia,x,y,wBR,aB2,TRUE);
x+=wBR+eC;

int wBCS=MedirTextoLargura(hFontAtual,traducoes[currentLangIndex].btnCpuSimilar)+(int)(30*esc);
if(wBCS<(int)(170*esc))wBCS=(int)(170*esc);
if(hBtnCpuSimilar)MoveWindow(hBtnCpuSimilar,x,y,wBCS,aB2,TRUE);

// Segunda linha de botoes, comecando embaixo do RANKING: evita cortar
// botao fora da tela quando a janela nao e larga o bastante pra caber
// tudo numa linha so.
y+=aL;
x=xRanking;

int wBCSs=MedirTextoLargura(hFontAtual,traducoes[currentLangIndex].btnCpuSimilarSingle)+(int)(30*esc);
if(wBCSs<(int)(210*esc))wBCSs=(int)(210*esc);
if(hBtnCpuSimilarSingle)MoveWindow(hBtnCpuSimilarSingle,x,y,wBCSs,aB2,TRUE);
x+=wBCSs+eC;

int wBCSm=MedirTextoLargura(hFontAtual,traducoes[currentLangIndex].btnCpuSimilarMulti)+(int)(30*esc);
if(wBCSm<(int)(210*esc))wBCSm=(int)(210*esc);
if(hBtnCpuSimilarMulti)MoveWindow(hBtnCpuSimilarMulti,x,y,wBCSm,aB2,TRUE);
x+=wBCSm+eC;

    y+=aL+(int)(4*esc);

    if(hChkFiltrarRepetidas){
        int wChk=(int)(560*esc);
        MoveWindow(hChkFiltrarRepetidas,15,y,wChk,(int)(22*esc),TRUE);
        y+=(int)(22*esc)+(int)(6*esc);
    }

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
        hBtnRanking,
        hBtnCpuSimilar,
        hBtnCpuSimilarSingle,
        hBtnCpuSimilarMulti,
        hBtnLimparCpu
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
if(hBtnEficiencia)SetWindowTextW(hBtnEficiencia,traducoes[li].btnEficiencia);
if(hChkFiltrarRepetidas)SetWindowTextW(hChkFiltrarRepetidas,traducoes[li].chkFiltrarRepetidas);
if(hBtnCpuSimilar)SetWindowTextW(hBtnCpuSimilar,traducoes[li].btnCpuSimilar);
if(hBtnCpuSimilarSingle)SetWindowTextW(hBtnCpuSimilarSingle,traducoes[li].btnCpuSimilarSingle);
if(hBtnCpuSimilarMulti)SetWindowTextW(hBtnCpuSimilarMulti,traducoes[li].btnCpuSimilarMulti);
if(hBtnLimparCpu)SetWindowTextW(hBtnLimparCpu,traducoes[li].btnLimparCpu);

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

    std::vector<size_t>idx=ObterIndicesFiltrados();

    std::sort(idx.begin(),idx.end(),[](size_t a,size_t b){
        return TotalBrutoSoma(pcsCadastrados[a].scoresMultiCore)>
               TotalBrutoSoma(pcsCadastrados[b].scoresMultiCore);
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

    // Substrings que devem ficar VERDES/VERMELHAS, na ORDEM em que aparecem
    // no documento final. A busca de posicao acontece DEPOIS, direto no
    // texto real do controle RichEdit (nao no std::wstring "lt" usado pra
    // montar o texto) — evita descompasso se o RichEdit contar \r\n de forma
    // diferente do wstring, que faria a cor "aterrissar" no lugar errado.
    std::vector<std::wstring> alvosVerdes;
    std::vector<std::wstring> alvosVermelhos;

    std::wstring lt=L"";

    lt+=L"===============================================================\r\n";
    lt+=traducoes[currentLangIndex].headerResult;
    lt+=L"\r\n===============================================================\r\n\r\n";

    // Sistema perfeito: nada de log10 nem soma de pontos. "Seu PC" e sempre a
    // ancora (100%); "Outro PC" e mostrado como percentual relativo a ela,
    // calculado pela media geometrica das razoes teste-a-teste (ver
    // IndiceGeometricoRelativo). So calculamos quando ha um PC selecionado —
    // sem parceiro nao ha razao pra comparar contra.
    double idxOutroSobreMeuMulti=1.0,idxOutroSobreMeuSingle=1.0;

    if(tc){
        idxOutroSobreMeuMulti=IndiceGeometricoRelativo(pcsCadastrados[ci].scoresMultiCore,meuUltimoScoreTestsMulti);
        idxOutroSobreMeuSingle=IndiceGeometricoRelativo(pcsCadastrados[ci].scoresSingleCore,meuUltimoScoreTestsSingle);
    }

    // Eficiencia de escalonamento: (Multi/Nucleos) / Single * 100%. Metrica
    // independente de comparacao com outro PC (cada CPU e comparada consigo
    // mesma), entao e calculada e mostrada mesmo sem parceiro selecionado.
    {
        double escMeu=CalcularEscalonamento(meuUltimoTotalMulti,meuUltimoTotalSingle,meuUltimoNumThreads);

        std::wstring blocoEsc=traducoes[currentLangIndex].escalonamentoLabel;
        blocoEsc+=L"\r\n";

        wchar_t linhaMeu[256];
        swprintf_s(linhaMeu,L"%-35s | %14.1f%%\r\n",traducoes[currentLangIndex].colSeuPC,escMeu);
        blocoEsc+=linhaMeu;

        if(tc){
            double escOutro=CalcularEscalonamento(pcsCadastrados[ci].totalMultiCore,pcsCadastrados[ci].totalSingleCore,pcsCadastrados[ci].numThreads);

            wchar_t linhaOutro[256];
            swprintf_s(linhaOutro,L"%-35s | %14.1f%%\r\n",traducoes[currentLangIndex].colOutroPC,escOutro);
            blocoEsc+=linhaOutro;
        }

        blocoEsc+=L"\r\n";
        lt+=blocoEsc;
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

        double meuVal=meuUltimoScoreTestsMulti[i];
        std::wstring meuFmt=FormatarNumero2Decimais(meuVal);

        if(tc){
            double outroVal=pcsCadastrados[ci].scoresMultiCore[i];
            std::wstring outroFmt=FormatarNumero2Decimais(outroVal);

            double d=0.0;
            if(meuVal>0.0&&outroVal>0.0){
                double maior=(meuVal>outroVal)?meuVal:outroVal;
                double menor=(meuVal<outroVal)?meuVal:outroVal;
                if(menor>0.0)d=((maior-menor)/menor)*100.0;
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

    if(tc){
        double percMeu=100.0;
        double percOutro=idxOutroSobreMeuMulti*100.0;

        // Dif SEMPRE relativa a quem for o mais LENTO dos dois (seja Seu PC
        // ou o Outro) — a mesma referencia dinamica usada nas linhas por
        // teste e no modal Resumo. Isso garante o MESMO numero em qualquer
        // tela, nao importa qual dos dois e mais rapido no momento.
        if(idxOutroSobreMeuMulti<1.0)
            dtm=(1.0/idxOutroSobreMeuMulti-1.0)*100.0;   // outro mais lento -> relativo a ele
        else if(idxOutroSobreMeuMulti>1.0)
            dtm=-(idxOutroSobreMeuMulti-1.0)*100.0;      // meu mais lento -> relativo a mim

        dtmFmt=FormatarNumero2Decimais(dtm<0.0?-dtm:dtm);

        wchar_t percMeuStr[32],percOutroStr[32];
        swprintf_s(percMeuStr,L"%.1f%%",percMeu);
        swprintf_s(percOutroStr,L"%.1f%%",percOutro);

        swprintf_s(t2,L"\r\n%-35s | %15s | %15s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            percMeuStr,
            percOutroStr,
            dtmFmt.c_str());

        lt+=t2;

        // Registra quais textos ficam verdes/vermelhos (a posicao real e
        // resolvida depois, direto no controle). Empate exato: nao colore.
        if(idxOutroSobreMeuMulti<1.0){
            alvosVerdes.push_back(percMeuStr);
            alvosVermelhos.push_back(percOutroStr);
        }else if(idxOutroSobreMeuMulti>1.0){
            alvosVermelhos.push_back(percMeuStr);
            alvosVerdes.push_back(percOutroStr);
            alvosVermelhos.push_back(dtmFmt+L"%");
        }

        // "Xx mais rapido": mesmo indice que ja gera a %, entao nunca pode
        // contradizer o numero da coluna Dif ao lado.
        {
            double vezes=(idxOutroSobreMeuMulti<1.0)?(1.0/idxOutroSobreMeuMulti):idxOutroSobreMeuMulti;
            std::wstring vezesFmt=FormatarVezes(vezes);
            const wchar_t*quemGanhou=(idxOutroSobreMeuMulti<1.0)?traducoes[currentLangIndex].colSeuPC:traducoes[currentLangIndex].colOutroPC;

            wchar_t vz[256];
            swprintf_s(vz,L"%-35s   %s %sx %s\r\n",L"",quemGanhou,vezesFmt.c_str(),traducoes[currentLangIndex].modalMaisRapido);
            lt+=vz;
        }
    }else{
        // Sem parceiro selecionado: mostra apenas a soma bruta como referencia
        // informativa (nao e "pontuacao" comparavel com nenhum outro PC).
        std::wstring totalMeuFmt=FormatarPontosFinal(TotalBrutoSoma(meuUltimoScoreTestsMulti));
        std::wstring totalMeuPts=totalMeuFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuPts.c_str());

        lt+=t2;
    }

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

        double meuVal=meuUltimoScoreTestsSingle[i];
        std::wstring meuFmt=FormatarNumero2Decimais(meuVal);

        if(tc){
            double outroVal=pcsCadastrados[ci].scoresSingleCore[i];
            std::wstring outroFmt=FormatarNumero2Decimais(outroVal);

            double d=0.0;
            if(meuVal>0.0&&outroVal>0.0){
                double maior=(meuVal>outroVal)?meuVal:outroVal;
                double menor=(meuVal<outroVal)?meuVal:outroVal;
                if(menor>0.0)d=((maior-menor)/menor)*100.0;
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

    if(tc){
        double percMeuS=100.0;
        double percOutroS=idxOutroSobreMeuSingle*100.0;

        if(idxOutroSobreMeuSingle<1.0)
            dts=(1.0/idxOutroSobreMeuSingle-1.0)*100.0;
        else if(idxOutroSobreMeuSingle>1.0)
            dts=-(idxOutroSobreMeuSingle-1.0)*100.0;

        std::wstring dtsFmt=FormatarNumero2Decimais(dts<0.0?-dts:dts);

        wchar_t percMeuStr[32],percOutroStr[32];
        swprintf_s(percMeuStr,L"%.1f%%",percMeuS);
        swprintf_s(percOutroStr,L"%.1f%%",percOutroS);

        swprintf_s(t2,L"\r\n%-35s | %15s | %15s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            percMeuStr,
            percOutroStr,
            dtsFmt.c_str());
    }else{
        std::wstring totalMeuSingleFmt=FormatarPontosFinal(TotalBrutoSoma(meuUltimoScoreTestsSingle));
        std::wstring totalMeuSinglePts=totalMeuSingleFmt+L" PTS";

        swprintf_s(t2,L"\r\n%-35s | %15s\r\n",
            traducoes[currentLangIndex].compTotal,
            totalMeuSinglePts.c_str());
    }

    lt+=t2;

    if(tc){
        wchar_t percMeuStrS[32],percOutroStrS[32];
        swprintf_s(percMeuStrS,L"%.1f%%",100.0);
        swprintf_s(percOutroStrS,L"%.1f%%",idxOutroSobreMeuSingle*100.0);

        if(idxOutroSobreMeuSingle<1.0){
            alvosVerdes.push_back(percMeuStrS);
            alvosVermelhos.push_back(percOutroStrS);
        }else if(idxOutroSobreMeuSingle>1.0){
            alvosVermelhos.push_back(percMeuStrS);
            alvosVerdes.push_back(percOutroStrS);

            std::wstring dtsFmtLocal=FormatarNumero2Decimais(dts<0.0?-dts:dts);
            alvosVermelhos.push_back(dtsFmtLocal+L"%");
        }
    }

    if(tc){
        double vezesS=(idxOutroSobreMeuSingle<1.0)?(1.0/idxOutroSobreMeuSingle):idxOutroSobreMeuSingle;
        std::wstring vezesSFmt=FormatarVezes(vezesS);
        const wchar_t*quemGanhouS=(idxOutroSobreMeuSingle<1.0)?traducoes[currentLangIndex].colSeuPC:traducoes[currentLangIndex].colOutroPC;

        wchar_t vzs[256];
        swprintf_s(vzs,L"%-35s   %s %sx %s\r\n",L"",quemGanhouS,vezesSFmt.c_str(),traducoes[currentLangIndex].modalMaisRapido);
        lt+=vzs;
    }

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
    AplicarCoresVencedoras(alvosVerdes);
    AplicarCoresPerdedoras(alvosVermelhos);
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

            double vA=sA[i];
            double vB=sB[i];

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

        // Sistema perfeito: CPU A e sempre a ancora (100%); CPU B e mostrada
        // como percentual relativo, calculado pela media geometrica das
        // razoes teste-a-teste (nunca soma de escalas diferentes).
        double idxBSobreA=IndiceGeometricoRelativo(sB,sA);

        double percA=100.0;
        double percB=idxBSobreA*100.0;

        // Dif SEMPRE relativa a quem for o mais LENTO dos dois (seja A ou B)
        // — a mesma referencia dinamica usada nas linhas por teste e no
        // modal Resumo. Garante o MESMO numero em qualquer tela.
        double dT;
        if(idxBSobreA<1.0)
            dT=(1.0/idxBSobreA-1.0)*100.0;   // B mais lento -> relativo a ele
        else if(idxBSobreA>1.0)
            dT=(idxBSobreA-1.0)*100.0;       // A mais lento -> relativo a ele
        else
            dT=0.0;

        wchar_t percAStr[32],percBStr[32];
        swprintf_s(percAStr,L"%.1f%%",percA);
        swprintf_s(percBStr,L"%.1f%%",percB);

        std::wstring dTFmt=FormatarNumero2Decimais(dT<0.0?-dT:dT);

        wchar_t ts[512];

        swprintf_s(ts,L"\r\n%-35s | %55s | %55s | %10s%%\r\n",
            traducoes[currentLangIndex].compTotal,
            percAStr,
            percBStr,
            dTFmt.c_str());

        lt+=ts;

        {
            double vezesAB=(idxBSobreA<1.0)?(1.0/idxBSobreA):idxBSobreA;
            std::wstring vezesABFmt=FormatarVezes(vezesAB);
            const std::wstring&quemGanhouAB=(idxBSobreA<1.0)?a.nome:b.nome;

            wchar_t vzab[512];
            swprintf_s(vzab,L"%-35s   %s %sx %s\r\n",L"",quemGanhouAB.c_str(),vezesABFmt.c_str(),traducoes[currentLangIndex].modalMaisRapido);
            lt+=vzab;
        }

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
if(hBtnEficiencia)EnableWindow(hBtnEficiencia,FALSE);

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

            std::wstring smFmt=FormatarNumero2Decimais(sm);

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

            std::wstring ssFmt=FormatarNumero2Decimais(ss);

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

        // meuUltimoTotalMulti/Single ja foram acumulados corretamente como soma
        // bruta dentro dos loops acima (nao precisam de nenhuma transformacao).
        std::wstring cpu=ObterNomeCompletoCPU();
        std::wstring nrpc=cpu+L" ("+std::to_wstring(nT)+L" Threads)";

        bool nR=false,en=false;

        for(size_t i=1;i<pcsCadastrados.size();++i){
            if(pcsCadastrados[i].nome==nrpc){
                en=true;

                if(meuUltimoTotalMulti>TotalBrutoSoma(pcsCadastrados[i].scoresMultiCore)){
                    pcsCadastrados[i].totalMultiCore=meuUltimoTotalMulti;
                    pcsCadastrados[i].numThreads=nT;

                    for(int j=0;j<100;++j)
                        pcsCadastrados[i].scoresMultiCore[j]=meuUltimoScoreTestsMulti[j];

                    nR=true;
                }

                if(meuUltimoTotalSingle>TotalBrutoSoma(pcsCadastrados[i].scoresSingleCore)){
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
if(hBtnEficiencia)EnableWindow(hBtnEficiencia,TRUE);

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
if(hBtnEficiencia)EnableWindow(hBtnEficiencia,TRUE);

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
if(hBtnEficiencia)EnableWindow(hBtnEficiencia,TRUE);

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

            hBtnLimparCpu=CreateWindowW(L"BUTTON",L"LIMPAR",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,90,30,hwnd,(HMENU)ID_BTN_LIMPAR_CPU,NULL,NULL);

            hBtnRun=CreateWindowW(L"BUTTON",L"Iniciar",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,90,30,hwnd,(HMENU)ID_BTN_RUN,NULL,NULL);

            hBtnResumo=CreateWindowW(L"BUTTON",L"\x26A1 RESUMO",WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_RESUMO,NULL,NULL);

            hBtnVerResultado=CreateWindowW(L"BUTTON",L"\x26A1 VER RESULTADO",WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_VER_RESULTADO,NULL,NULL);

            hBtnRanking=CreateWindowW(L"BUTTON",L"\x2605 RANKING",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_RANKING,NULL,NULL);
hBtnEficiencia=CreateWindowW(L"BUTTON",L"\x2699 EFICIENCIA",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,130,30,hwnd,(HMENU)ID_BTN_EFICIENCIA,NULL,NULL);
hBtnCpuSimilar=CreateWindowW(L"BUTTON",L"CPU MAIS SEMELHANTE",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,170,30,hwnd,(HMENU)ID_BTN_CPU_SIMILAR,NULL,NULL);
hBtnCpuSimilarSingle=CreateWindowW(L"BUTTON",L"CPU MAIS PROXIMA (SINGLE-CORE)",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,210,30,hwnd,(HMENU)ID_BTN_CPU_SIMILAR_SINGLE,NULL,NULL);
hBtnCpuSimilarMulti=CreateWindowW(L"BUTTON",L"CPU MAIS PROXIMA (MULTI-CORE)",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,15,15,210,30,hwnd,(HMENU)ID_BTN_CPU_SIMILAR_MULTI,NULL,NULL);
hChkFiltrarRepetidas=CreateWindowW(L"BUTTON",traducoes[currentLangIndex].chkFiltrarRepetidas,WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX,15,15,400,22,hwnd,(HMENU)ID_CHK_FILTRAR_REPETIDAS,NULL,NULL);

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

            SincronizarDadosInicializacao(hwnd);
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
else if(LOWORD(wParam)==ID_BTN_EFICIENCIA&&HIWORD(wParam)==BN_CLICKED){
AbrirEficiencia();
}
else if(LOWORD(wParam)==ID_BTN_CPU_SIMILAR&&HIWORD(wParam)==BN_CLICKED){
    ExecutarBuscaCpuSimilar(true,true);
}
else if(LOWORD(wParam)==ID_BTN_CPU_SIMILAR_SINGLE&&HIWORD(wParam)==BN_CLICKED){
    ExecutarBuscaCpuSimilar(false,true);
}
else if(LOWORD(wParam)==ID_BTN_CPU_SIMILAR_MULTI&&HIWORD(wParam)==BN_CLICKED){
    ExecutarBuscaCpuSimilar(true,false);
}
else if(LOWORD(wParam)==ID_BTN_LIMPAR_CPU&&HIWORD(wParam)==BN_CLICKED){
    // Desmarca CPU A e CPU B, voltando os dois pra "Selecione uma CPU...".
    if(hComboCpuA)SendMessageW(hComboCpuA,CB_SETCURSEL,0,0);
    if(hComboCpuB)SendMessageW(hComboCpuB,CB_SETCURSEL,0,0);

    AtualizarPainelPrincipal();
}
else if(LOWORD(wParam)==ID_CHK_FILTRAR_REPETIDAS&&HIWORD(wParam)==BN_CLICKED){
    g_filtrarCpusRepetidas=(SendMessageW(hChkFiltrarRepetidas,BM_GETCHECK,0,0)==BST_CHECKED);
    AtualizarListaComparacao();
    if(hEficienciaWnd)InvalidateRect(hEficienciaWnd,NULL,TRUE);
    if(hRankingWnd)InvalidateRect(hRankingWnd,NULL,TRUE);
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