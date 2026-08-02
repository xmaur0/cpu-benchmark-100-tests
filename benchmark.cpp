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
#include <exception> // Importante para o try-catch
#pragma comment(lib, "wininet.lib")

#define ID_BTN_RUN 101
#define ID_COMBO_LANG 102
#define ID_COMBO_PC_COMPARE 103
#define ID_COMBO_FONT 106
#define ID_EDIT_LOG 104
#define ID_STATIC_LANG 201
#define ID_STATIC_COMPARE 202
#define ID_STATIC_STATUS 203
#define ID_STATIC_FONT 204

const wchar_t* NPOINT_URL = L"https://api.npoint.io/xxxx"; 

struct IdiomaTextos {
    const wchar_t* tituloJanela;
    const wchar_t* labelLang;
    const wchar_t* labelCompare;
    const wchar_t* labelFont;
    const wchar_t* labelSort;
    const wchar_t* labelModo;
    const wchar_t* btnRun;
    const wchar_t* btnComparador;
    const wchar_t* statusPronto;
    const wchar_t* statusRodandoMulti;
    const wchar_t* statusRodandoSingle;
    const wchar_t* headerResult;
    const wchar_t* lblThreads;
    const wchar_t* colTeste;
    const wchar_t* colSeuPC;
    const wchar_t* colOutroPC;
    const wchar_t* colDif;
    const wchar_t* colPontuacao;
    const wchar_t* selecionePC;
    const wchar_t* avisoRodarPrimeiro;
    const wchar_t* sortScore;
    const wchar_t* sortCores;
    const wchar_t* sortAlpha;
    const wchar_t* modoMulti;
    const wchar_t* modoSingle;
    const wchar_t* modoAmbos;
    const wchar_t* compTitulo;
    const wchar_t* compCpu1;
    const wchar_t* compCpu2;
    const wchar_t* compCpu3;
    const wchar_t* compCpu4;
    const wchar_t* compTipo;
    const wchar_t* compResumido;
    const wchar_t* compDetalhado;
    const wchar_t* compComparar;
    const wchar_t* compFechar;
    const wchar_t* compMultiCore;
    const wchar_t* compSingleCore;
    const wchar_t* compTotal;
    const wchar_t* statusExecutandoTudo;
    const wchar_t* msgMaisRapido;
    const wchar_t* msgMaisLento;
    const wchar_t* msgEmpate;
    const wchar_t* msgSelecioneParaComparar;
    const wchar_t* tituloErro;
    const wchar_t* msgErroBenchmark;
    const wchar_t* msgErroDesconhecido;
    const wchar_t* statusErroBenchmark;
    const wchar_t* tituloAguarde;
    const wchar_t* msgAguardeFechar;
    const wchar_t* nomesTestes[100];
};

// Definição dos nomes dos testes em Português (Base)
const wchar_t* nomesTestesPT[100] = {
    L"01. Ponto Flutuante", L"02. Matriz Inteiros", L"03. Ordenacao Dados", L"04. Numeros Primos",
    L"05. Alocacao Heap", L"06. Operacoes Bitwise", L"07. Funcao Hash", L"08. Estresse Cache",
    L"09. Polinomios", L"10. Logica Arrays", L"11. Criptografia SHA", L"12. Compressao RLE",
    L"13. Fisica N-Corpos", L"14. Simulacao Vida", L"15. Sintese Audio",
    L"16. Processamento Rede", L"17. IA Perceptron", L"18. Busca Database",
    L"19. Render Particulas", L"20. Steganografia LSB", L"21. Fractal Mandelbrot",
    L"22. Transformada Fourier", L"23. Caminho Minimo", L"24. Compilador Regex", L"25. Motor XML",
    L"26. Multiplicacao Matriz", L"27. Ray Tracing Simples", L"28. Algoritmo Genetico",
    L"29. Simulacao Fluidos", L"30. Cifra AES Simulada", L"31. Pathfinding A*",
    L"32. Monte Carlo Pi", L"33. Convolucao Imagem", L"34. Arvore B-Tree", L"35. Calculo Tensorial",
    L"36. Fatorial Recursivo", L"37. Sequencia Fibonacci", L"38. Torre de Hanoi",
    L"39. Crivo de Eratostenes", L"40. MDC Euclides", L"41. Potencia Modular",
    L"42. Raiz Quadrada Newton", L"43. Seno Taylor Series", L"44. Exponencial Math",
    L"45. Logaritmo Natural", L"46. Valor Absoluto Bulk", L"47. Arredondamento Bulk",
    L"48. Clamp Values", L"49. Lerp Linear", L"50. Spline Cubica",
    L"51. Bubble Sort", L"52. Insertion Sort", L"53. Selection Sort",
    L"54. Quick Sort Pivot", L"55. Merge Sort", L"56. Heap Sort",
    L"57. Counting Sort", L"58. Radix Sort", L"59. Bucket Sort",
    L"60. Shell Sort", L"61. String Copy", L"62. String Concat",
    L"63. String Compare", L"64. String Find", L"65. String Reverse",
    L"66. String To Upper", L"67. String Trim", L"68. CSV Parse",
    L"69. JSON Tokenizer", L"70. Base64 Encode", L"71. Hex Dump",
    L"72. Checksum CRC32", L"73. Adler32 Check", L"74. Fletcher Checksum",
    L"75. XOR Cipher", L"76. ROT13 Cipher", L"77. Caesar Cipher",
    L"78. Vigenere Cipher", L"79. Random Fill", L"80. Memory Set",
    L"81. Memory Move", L"82. Vector Add", L"83. Vector Dot Product",
    L"84. Vector Cross Product", L"85. Matrix Determinant", L"86. Matrix Inverse",
    L"87. Linked List Traverse", L"88. Binary Search Tree", L"89. Hash Map Ops",
    L"90. Priority Queue", L"91. Stack Push Pop", L"92. Queue Enqueue Dequeue",
    L"93. Graph DFS", L"94. Graph BFS", L"95. Dijkstra Simple",
    L"96. Floyd Warshall", L"97. Knapsack DP", L"98. LCS Dynamic",
    L"99. Edit Distance", L"100. Prime Factorization"
};

// Traduções completas
IdiomaTextos traducoes[] = {
    // 0: Portuguese
    { L"Benchmark Multi-Core C++ (100 Tests)", L"Idioma:", L"Comparar com:", L"Fonte:", L"Ordenar por:", L"Modo:", 
      L"Iniciar Benchmark", L"Comparador",
      L"Pronto para iniciar.", L"Executando 100 testes MULTI-CORE... Aguarde...", L"Executando 100 testes SINGLE-CORE... Aguarde...",
      L"RESULTADO FINAL (100 TESTES)", L"Nucleos/Threads Detectados: ",
      L"Teste", L"Seu PC", L"Outro PC", L"Diferenca", L"Pontuacao", 
      L"Selecione um PC para comparar...", L"Execute o benchmark primeiro.",
      L"Maior Pontuacao", L"Qtd. Nucleos", L"Ordem Alfabetica",
      L"Multi-Core", L"Single-Core", L"Ambos",
      L"Comparador Multi-CPUs", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Tipo de Teste:", L"Resumido (% diferenca)", L"Detalhado (100 testes)",
      L"Comparar", L"Fechar", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTAL <<", L"Executando 100 testes (Multi + Single)... Aguarde...", L"*** SEU PC E MAIS RAPIDO (+", L"*** SEU PC E MAIS LENTO (", L"*** EMPATE TECNICO ***", L"*** SELECIONE UM PC PARA VER A COMPARACAO ***", L"Erro", L"Ocorreu um erro durante o benchmark.", L"Ocorreu um erro desconhecido.", L"Erro no benchmark.", L"Aguarde", L"Aguarde o termino do benchmark antes de fechar.", {} },
      
    // 1: English
    { L"C++ Multi-Core Benchmark (100 Tests)", L"Language:", L"Compare with:", L"Font:", L"Sort by:", L"Mode:", 
      L"Start Benchmark", L"Comparator",
      L"Ready to start.", L"Running 100 MULTI-CORE tests... Please wait...", L"Running 100 SINGLE-CORE tests... Please wait...",
      L"FINAL SCORE (100 TESTS)", L"Detected Cores/Threads: ",
      L"Test", L"Your PC", L"Other PC", L"Difference", L"Score", 
      L"Select a PC to compare...", L"Please run the benchmark first.",
      L"Highest Score", L"Core Count", L"Alphabetical",
      L"Multi-Core", L"Single-Core", L"Both",
      L"Multi-CPUs Comparator", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Test Type:", L"Summary (% difference)", L"Detailed (100 tests)",
      L"Compare", L"Close", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTAL <<", L"Running 100 tests (Multi + Single)... Please wait...", L"*** YOUR PC IS FASTER (+", L"*** YOUR PC IS SLOWER (", L"*** TECHNICAL TIE ***", L"*** SELECT A PC TO SEE THE COMPARISON ***", L"Error", L"An error occurred during the benchmark.", L"An unknown error occurred.", L"Benchmark error.", L"Please Wait", L"Please wait for the benchmark to finish before closing.", {} },

    // 2: Spanish
    { L"Benchmark Multi-Core C++ (100 Tests)", L"Idioma:", L"Comparar con:", L"Fuente:", L"Ordenar por:", L"Modo:", 
      L"Iniciar Pruebas", L"Comparador",
      L"Listo.", L"Ejecutando 100 pruebas MULTI-CORE...", L"Ejecutando 100 pruebas SINGLE-CORE...",
      L"PUNTUACION FINAL", L"Nucleos:",
      L"Prueba", L"Tu PC", L"Otro PC", L"Diferencia", L"Puntuacion", 
      L"Selecciona un PC para comparar...", L"Ejecuta el benchmark primero.",
      L"Mayor Puntuacion", L"Cant. Nucleos", L"Alfabetico",
      L"Multi-Core", L"Single-Core", L"Ambos",
      L"Comparador Multi-CPUs", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Tipo de Prueba:", L"Resumen (% diferencia)", L"Detallado (100 pruebas)",
      L"Comparar", L"Cerrar", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTAL <<", L"Ejecutando 100 pruebas (Multi + Single)... Espera...", L"*** TU PC ES MAS RAPIDA (+", L"*** TU PC ES MAS LENTA (", L"*** EMPATE TECNICO ***", L"*** SELECCIONA UN PC PARA VER LA COMPARACION ***", L"Error", L"Ocurrio un error durante el benchmark.", L"Ocurrio un error desconocido.", L"Error en el benchmark.", L"Espera", L"Espera a que termine el benchmark antes de cerrar.", {} },

    // 3: French
    { L"Test C++ (100 Tests)", L"Langue:", L"Comparer:", L"Police:", L"Trier:", L"Mode:", 
      L"Demarrer", L"Comparateur",
      L"Pret.", L"100 tests MULTI-CORE...", L"100 tests SINGLE-CORE...",
      L"SCORE FINAL", L"Coeurs:",
      L"Test", L"Votre PC", L"Autre PC", L"Difference", L"Score", 
      L"Selectionnez un PC...", L"Executez le benchmark d'abord.",
      L"Meilleur Score", L"Nb. Coeurs", L"Alphabetique",
      L"Multi-Core", L"Single-Core", L"Les deux",
      L"Comparateur Multi-CPUs", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Type de Test:", L"Resume (% diff)", L"Detaille (100 tests)",
      L"Comparer", L"Fermer", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTAL <<", L"Execution de 100 tests (Multi + Single)... Veuillez patienter...", L"*** VOTRE PC EST PLUS RAPIDE (+", L"*** VOTRE PC EST PLUS LENT (", L"*** EGALITE TECHNIQUE ***", L"*** SELECTIONNEZ UN PC POUR VOIR LA COMPARAISON ***", L"Erreur", L"Une erreur s'est produite pendant le benchmark.", L"Une erreur inconnue s'est produite.", L"Erreur du benchmark.", L"Veuillez patienter", L"Veuillez attendre la fin du benchmark avant de fermer.", {} },

    // 4: German
    { L"C++ Benchmark (100 Tests)", L"Sprache:", L"Vergleichen:", L"Schrift:", L"Sortieren:", L"Modus:", 
      L"Starten", L"Vergleicher",
      L"Bereit.", L"100 MULTI-CORE Tests...", L"100 SINGLE-CORE Tests...",
      L"ERGEBNIS", L"Kerne:",
      L"Test", L"Ihr PC", L"Anderer PC", L"Differenz", L"Punktzahl", 
      L"PC zum Vergleichen...", L"Bitte zuerst starten.",
      L"Hochste Punktzahl", L"Kernanzahl", L"Alphabetisch",
      L"Multi-Core", L"Single-Core", L"Beide",
      L"Multi-CPUs Vergleicher", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Testtyp:", L"Zusammenfassung (%)", L"Detailliert (100 Tests)",
      L"Vergleichen", L"Schliessen", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> GESAMT <<", L"Fuhre 100 Tests aus (Multi + Single)... Bitte warten...", L"*** IHR PC IST SCHNELLER (+", L"*** IHR PC IST LANGSAMER (", L"*** TECHNISCHES UNENTSCHIEDEN ***", L"*** WAEHLEN SIE EINEN PC FUER DEN VERGLEICH ***", L"Fehler", L"Waehrend des Benchmarks ist ein Fehler aufgetreten.", L"Ein unbekannter Fehler ist aufgetreten.", L"Benchmark-Fehler.", L"Bitte warten", L"Bitte warten Sie, bis der Benchmark beendet ist, bevor Sie schliessen.", {} },

    // 5: Italian
    { L"Benchmark C++ (100 Tests)", L"Lingua:", L"Confronta:", L"Font:", L"Ordina:", L"Modo:", 
      L"Avvia", L"Comparatore",
      L"Pronto.", L"100 test MULTI-CORE...", L"100 test SINGLE-CORE...",
      L"PUNTEGGIO", L"Core:",
      L"Test", L"Tuo PC", L"Altro PC", L"Differenza", L"Punteggio", 
      L"Seleziona un PC...", L"Esegui prima il benchmark.",
      L"Punteggio Piu Alto", L"Num. Core", L"Alfabetico",
      L"Multi-Core", L"Single-Core", L"Entrambi",
      L"Comparatore Multi-CPUs", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Tipo di Test:", L"Riassunto (%)", L"Dettagliato (100 test)",
      L"Confronta", L"Chiudi", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTALE <<", L"Esecuzione di 100 test (Multi + Single)... Attendere...", L"*** IL TUO PC E PIU VELOCE (+", L"*** IL TUO PC E PIU LENTO (", L"*** PAREGGIO TECNICO ***", L"*** SELEZIONA UN PC PER VEDERE IL CONFRONTO ***", L"Errore", L"Si e verificato un errore durante il benchmark.", L"Si e verificato un errore sconosciuto.", L"Errore nel benchmark.", L"Attendere", L"Attendi il termine del benchmark prima di chiudere.", {} },

    // 6: Chinese
    { L"C++ Benchmark (100 Tests)", L"Yan Yu:", L"Bi Jiao:", L"Zi Ti:", L"Pai Xu:", L"Mo Shi:", 
      L"Kai Shi", L"Bi Jiao Qi",
      L"Jiu Xu", L"100 ge duo he xin ce shi...", L"100 ge dan he xin ce shi...",
      L"Zui Zhong De Fen", L"He Xin:",
      L"Ce Shi", L"Ni De Dian Nao", L"Qi Ta Dian Nao", L"Cha Yi", L"Fen Shu", 
      L"Xuan Ze Yao Bi Jiao De Dian Nao...", L"Qing Xian Yun Xing Ce Shi.",
      L"Zui Gao Fen", L"He Xin Shu Liang", L"Zi Mu Shun Xu",
      L"Duo He Xin", L"Dan He Xin", L"Liang Zhe",
      L"Duo CPU Bi Jiao Qi", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Ce Shi Lei Xing:", L"Zhai Yao (%)", L"Xiang Xi (100 ce shi)",
      L"Bi Jiao", L"Guan Bi", L"[Duo He Xin]", L"[Dan He Xin]",
      L">> Zong Ji <<", L"Zheng Zai Yun Xing 100 Ce Shi (Duo He Dan He)... Qing Deng...", L"*** Ni De Dian Nao Geng Kuai (+", L"*** Ni De Dian Nao Geng Man (", L"*** Ji Shu Ping Ju ***", L"*** Xuan Ze Yi Tai Dian Nao Yi Cha Kan Bi Jiao ***", L"Cuo Wu", L"Ce Shi Guo Cheng Zhong Fa Sheng Cuo Wu.", L"Fa Sheng Wei Zhi Cuo Wu.", L"Ce Shi Cuo Wu.", L"Qing Deng Dai", L"Qing Deng Ce Shi Wan Cheng Zai Guan Bi.", {} },

    // 7: Russian
    { L"C++ Benchmark (100 Tests)", L"Yazyk:", L"Sravnit:", L"Shrift:", L"Sort:", L"Rezhim:", 
      L"Start", L"Komparator",
      L"Gotov.", L"100 MULTI-CORE testov...", L"100 SINGLE-CORE testov...",
      L"ITOG", L"Yadra:",
      L"Test", L"Vash PK", L"Drugoy PK", L"Raznica", L"Rezultat", 
      L"Vyberite PK...", L"Snachala zapustite test.",
      L"Luchshiy rezultat", L"Kol-vo yader", L"Po alfavitu",
      L"Multi-Core", L"Single-Core", L"Oba",
      L"Multi-CPU Komparator", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Tip testa:", L"Kratko (%)", L"Podrobno (100 testov)",
      L"Sravnit", L"Zakryt", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> ITOGO <<", L"Vypolnenie 100 testov (Multi + Single)... Pozhaluysta podozhdite...", L"*** VASH PK BYSTREE (+", L"*** VASH PK MEDLENNEE (", L"*** TEKHNICHESKAYA NICHYA ***", L"*** VYBERITE PK DLYA SRAVNENIYA ***", L"Oshibka", L"Proizoshla oshibka vo vremya testa.", L"Proizoshla neizvestnaya oshibka.", L"Oshibka testa.", L"Pozhaluysta podozhdite", L"Pozhaluysta dozhdites okonchaniya testa pered zakrytiem.", {} },

    // 8: Korean
    { L"C++ Benchmark (100 Tests)", L"Eon Eo:", L"Bi Gyo:", L"Geul Ggol:", L"Jeong Ryeol:", L"Mo Deu:", 
      L"Si Jak", L"Bi Gyo Gi",
      L"Jun Bi", L"100 MULTI-CORE testeu...", L"100 SINGLE-CORE testeu...",
      L"Choe Jong Jeom Su", L"Ko Eo:",
      L"Te Seuteu", L"Nae PC", L"Da Reun PC", L"Cha I", L"Jeom Su", 
      L"Bi Gyo Hal PC Seon Taek...", L"Meon Jeo Beon Chi Ma Keu Reul Sil Haeng Ha Se Yo.",
      L"Choe Go Jeom Su", L"Ko Eo Su", L"Al Pa Bet Sun",
      L"Meol Ti Ko Eo", L"Sing Geul Ko Eo", L"Dul Da",
      L"Meol Ti CPU Bi Gyo Gi", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Te Seuteu Yu Hyeong:", L"Yo Yak (%)", L"Sang Se (100 te seuteu)",
      L"Bi Gyo", L"Dat Gi", L"[Meol Ti Ko Eo]", L"[Sing Geul Ko Eo]",
      L">> Hab Gye <<", L"100 Ge Ui Te Seuteu Sil Haeng Jung (Multi + Single)... Gi Da Ryeo Ju Se Yo...", L"*** Nae PC Ga Deo Ppa Reum (+", L"*** Nae PC Ga Deo Neu Rim (", L"*** Gi Sul Jeok Mu Seung Bu ***", L"*** Bi Gyo Reul Bo Ryeo Myeon PC Reul Seon Taek Ha Se Yo ***", L"O Ryu", L"Ben Chi Ma Keu Jung O Ryu Ga Bal Saeng Haet Seum Ni Da.", L"Al Su Eom Neun O Ryu Ga Bal Saeng Haet Seum Ni Da.", L"Ben Chi Ma Keu O Ryu.", L"Gi Da Ryeo Ju Se Yo", L"Dat Gi Jeon E Ben Chi Ma Keu Ga Kkeun Na Gi Reul Gi Da Ryeo Ju Se Yo.", {} },

    // 9: Dutch
    { L"C++ Benchmark (100 Tests)", L"Taal:", L"Vergelijk:", L"Lettertype:", L"Sorteer:", L"Modus:", 
      L"Start", L"Vergelijker",
      L"Klaar.", L"100 MULTI-CORE tests...", L"100 SINGLE-CORE tests...",
      L"Resultaat", L"Kernen:",
      L"Test", L"Jouw PC", L"Andere PC", L"Verschil", L"Score", 
      L"Selecteer een PC...", L"Voer eerst de benchmark uit.",
      L"Hoogste Score", L"Aantal Kernen", L"Alfabetisch",
      L"Multi-Core", L"Single-Core", L"Beide",
      L"Multi-CPU Vergelijker", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Test Type:", L"Samenvatting (%)", L"Gedetailleerd (100 tests)",
      L"Vergelijk", L"Sluiten", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> TOTAAL <<", L"100 tests uitvoeren (Multi + Single)... Even geduld...", L"*** JOUW PC IS SNELLER (+", L"*** JOUW PC IS LANGZAMER (", L"*** TECHNISCH GELIJKSPEL ***", L"*** SELECTEER EEN PC OM TE VERGELIJKEN ***", L"Fout", L"Er is een fout opgetreden tijdens de benchmark.", L"Er is een onbekende fout opgetreden.", L"Benchmarkfout.", L"Even geduld", L"Wacht tot de benchmark is voltooid voordat u sluit.", {} },

    // 10: Polish
    { L"Benchmark C++ (100 Tests)", L"Jezyk:", L"Porownaj:", L"Czcionka:", L"Sortuj:", L"Tryb:", 
      L"Start", L"Porownywarka",
      L"Gotowy.", L"100 testow MULTI-CORE...", L"100 testow SINGLE-CORE...",
      L"Wynik", L"Rdzenie:",
      L"Test", L"Twoj PC", L"Inny PC", L"Roznica", L"Wynik", 
      L"Wybierz PC...", L"Najpierw uruchom test.",
      L"Najwyzszy Wynik", L"Liczba Rdzeni", L"Alfabetycznie",
      L"Multi-Core", L"Single-Core", L"Oba",
      L"Multi-CPU Porownywarka", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Typ Testu:", L"Podsumowanie (%)", L"Szczegolowy (100 testow)",
      L"Porownaj", L"Zamknij", L"[MULTI-CORE]", L"[SINGLE-CORE]",
      L">> RAZEM <<", L"Wykonywanie 100 testow (Multi + Single)... Prosze czekac...", L"*** TWOJ PC JEST SZYBSZY (+", L"*** TWOJ PC JEST WOLNIEJSZY (", L"*** REMIS TECHNICZNY ***", L"*** WYBIERZ PC ABY ZOBACZYC POROWNANIE ***", L"Blad", L"Wystapil blad podczas testu.", L"Wystapil nieznany blad.", L"Blad testu.", L"Prosze czekac", L"Prosze czekac na zakonczenie testu przed zamknieciem.", {} },

    // 11: Japanese
    { L"C++ Benchmark (100 Tests)", L"Nihongo:", L"Hikaku:", L"Font:", L"Narabekae:", L"Moodo:", 
      L"Kaishi", L"Hikaku Tsuuru",
      L"Junbi Kanryou", L"100 MULTI-CORE tesuto...", L"100 SINGLE-CORE tesuto...",
      L"Saishuu Sukoa", L"Koa:",
      L"Tesuto", L"Anata no PC", L"Hoka no PC", L"Sai", L"Sukoa", 
      L"Hikaku Suru PC Wo Sentaku...", L"Saisho Ni Benchmark Wo Jikkou Shite Kudasai.",
      L"Saikou Sukoa", L"Koa Suu", L"Arufabetto Jun",
      L"Maruchi Koa", L"Shinguru Koa", L"Ryouhou",
      L"Maruchi CPU Hikaku Tsuuru", L"CPU 1:", L"CPU 2:", L"CPU 3:", L"CPU 4:",
      L"Tesuto Taipu:", L"Gaiyou (%)", L"Shousai (100 tesuto)",
      L"Hikaku", L"Tojiru", L"[Maruchi Koa]", L"[Shinguru Koa]",
      L">> Goukei <<", L"100 No Tesuto Wo Jikkou Chuu (Multi + Single)... Omachi Kudasai...", L"*** Anata No PC No Hou Ga Hayai (+", L"*** Anata No PC No Hou Ga Osoi (", L"*** Gijutsuteki Ni Hikiwake ***", L"*** Hikaku Wo Miru Ni Wa PC Wo Sentaku Shite Kudasai ***", L"Era", L"Benchimaku Chuu Ni Era Ga Hassei Shimashita.", L"Fumei Na Era Ga Hassei Shimashita.", L"Benchimaku Era.", L"Omachi Kudasai", L"Tojiru Mae Ni Benchimaku No Shuuryou Wo Omachi Kudasai.", {} }
};

HWND hEditLog = NULL;
HWND hBtnRun = NULL;
HWND hComboLang = NULL;
HWND hComboCompare = NULL;
HWND hComboFont = NULL;
HWND hStaticLang = NULL;
HWND hStaticCompare = NULL;
HWND hStaticStatus = NULL;
HWND hStaticFont = NULL;
HWND hMainWnd = NULL; // Handle global da janela principal

HFONT hFontAtual = NULL;
int currentFontSize = 21;
int currentLangIndex = 0;
int g_winW = 1400;
int g_winH = 700;

struct PCReferencia {
    std::wstring nome;
    double scoresMultiCore[100];
    double scoresSingleCore[100];
    double totalMultiCore;
    double totalSingleCore;
    int numThreads;
};

std::vector<PCReferencia> pcsCadastrados = {
    { L"Selecione um PC para comparar...", {0}, {0}, 0.0, 0.0, 0 }
};

double meuUltimoScoreTestsMulti[100] = { 0 };
double meuUltimoScoreTestsSingle[100] = { 0 };
double meuUltimoTotalMulti = 0;
double meuUltimoTotalSingle = 0;
int meuUltimoNumThreads = 0;
bool benchmarkRealizado = false;
bool benchmarkEmAndamento = false; // Flag para controlar estado

void AtualizarFontesSimples(int fontSize);
void AtualizarIdiomaInterface(int langIndex);
void AtualizarPainelComparativo();
void AtualizarListaComparacao();
void PosicionarControlesTopo();

std::wstring Utf8ToWstring(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string WstringToUtf8(const std::wstring& wstr) {
    if (wstr.empty()) return "";
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::wstring ObterNomeCompletoCPU() {
    HKEY hKey;
    wchar_t buffer[256] = L"CPU Desconhecido";
    DWORD bufferSize = sizeof(buffer);
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExW(hKey, L"ProcessorNameString", NULL, NULL, (LPBYTE)buffer, &bufferSize);
        RegCloseKey(hKey);
    }
    std::wstring nome(buffer);
    size_t lastChar = nome.find_last_not_of(L"\r\n\t ");
    if (lastChar != std::wstring::npos) {
        nome.erase(lastChar + 1);
    }
    return nome;
}

std::string GerarJsonCompleto() {
    std::string json = "{\"data\":[";
    for (size_t i = 1; i < pcsCadastrados.size(); ++i) {
        if (i > 1) json += ",";
        std::wstring nomeEscapado = pcsCadastrados[i].nome;
        size_t pos = 0;
        while ((pos = nomeEscapado.find(L'"', pos)) != std::wstring::npos) {
            nomeEscapado.replace(pos, 1, L"\\\"");
            pos += 2;
        }
        json += "{";
        json += "\"nome\":\"" + WstringToUtf8(nomeEscapado) + "\",";
        json += "\"totalMulti\":" + std::to_string(pcsCadastrados[i].totalMultiCore) + ",";
        json += "\"totalSingle\":" + std::to_string(pcsCadastrados[i].totalSingleCore) + ",";
        json += "\"threads\":" + std::to_string(pcsCadastrados[i].numThreads) + ",";
        json += "\"scoresMulti\":[";
        for (int j = 0; j < 100; ++j) {
            json += std::to_string(pcsCadastrados[i].scoresMultiCore[j]);
            if (j < 99) json += ",";
        }
        json += "],\"scoresSingle\":[";
        for (int j = 0; j < 100; ++j) {
            json += std::to_string(pcsCadastrados[i].scoresSingleCore[j]);
            if (j < 99) json += ",";
        }
        json += "]}";
    }
    json += "]}";
    return json;
}

bool SalvarListaNuvemNativo() {
    std::string jsonData = GerarJsonCompleto();
    HINTERNET hSession = InternetOpenW(L"BenchmarkClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hSession) return false;
    HINTERNET hConnect = InternetConnectW(hSession, L"api.npoint.io", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) { InternetCloseHandle(hSession); return false; }
    HINTERNET hRequest = HttpOpenRequestW(hConnect, L"POST", L"/701d17865ab4488e439e", NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
    if (!hRequest) { InternetCloseHandle(hConnect); InternetCloseHandle(hSession); return false; }
    std::wstring headers = L"Content-Type: application/json\r\nAccept: */*\r\n";
    BOOL enviado = HttpSendRequestW(hRequest, headers.c_str(), (DWORD)headers.size(), (LPVOID)jsonData.c_str(), (DWORD)jsonData.size());
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    return enviado == TRUE;
}

// Função auxiliar robusta para extrair array de doubles do JSON
std::vector<double> ExtrairArrayDouble(const std::string& json, size_t startPos) {
    std::vector<double> result;
    size_t pos = json.find('[', startPos);
    if (pos == std::string::npos) return result;
    
    pos++; // Pula '['
    while (pos < json.size()) {
        // Ignora espaços
        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) pos++;
        
        if (json[pos] == ']') break; // Fim do array
        
        size_t numStart = pos;
        // Procura fim do número (vírgula ou colchete)
        while (pos < json.size() && json[pos] != ',' && json[pos] != ']') pos++;
        
        if (pos > numStart) {
            try {
                std::string numStr = json.substr(numStart, pos - numStart);
                result.push_back(std::stod(numStr));
            } catch (...) {
                // Falha ao converter, ignora
            }
        }
        
        if (pos < json.size() && json[pos] == ',') pos++; // Pula vírgula
    }
    return result;
}

void CarregarListaNuvem(HWND hwnd) {
    HINTERNET hInternet = InternetOpenW(L"BenchmarkAppClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return;
    HINTERNET hFile = InternetOpenUrlW(hInternet, NPOINT_URL, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 0);
    if (hFile) {
        std::string resposta;
        char buffer[4096];
        DWORD bytesLidos = 0;
        while (InternetReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesLidos) && bytesLidos > 0) {
            buffer[bytesLidos] = '\0';
            resposta += buffer;
        }
        InternetCloseHandle(hFile);
        
        size_t posArray = resposta.find("\"data\":[");
        if (posArray != std::string::npos) {
            size_t pos = posArray + 7;
            while ((pos = resposta.find("{\"nome\"", pos)) != std::string::npos) {
                size_t startNome = resposta.find(":\"", pos) + 2;
                size_t endNome = resposta.find("\"", startNome);
                if (startNome == std::string::npos || endNome == std::string::npos) break;
                
                std::string nomeUtf8 = resposta.substr(startNome, endNome - startNome);
                std::wstring wNome = Utf8ToWstring(nomeUtf8);
                
                double totalMulti = 0, totalSingle = 0;
                int threads = 0;
                
                // Extração segura de totais
                size_t posTotalMulti = resposta.find("\"totalMulti\":", endNome);
                if (posTotalMulti != std::string::npos) {
                    try { totalMulti = std::stod(resposta.substr(posTotalMulti + 13)); } catch(...) {}
                }
                size_t posTotalSingle = resposta.find("\"totalSingle\":", endNome);
                if (posTotalSingle != std::string::npos) {
                    try { totalSingle = std::stod(resposta.substr(posTotalSingle + 14)); } catch(...) {}
                }
                size_t posThreads = resposta.find("\"threads\":", endNome);
                if (posThreads != std::string::npos) {
                    try { threads = std::stoi(resposta.substr(posThreads + 10)); } catch(...) {}
                }
                
                // Extração robusta dos arrays de scores
                std::vector<double> scoresMultiVec = ExtrairArrayDouble(resposta, endNome);
                // Precisamos achar o segundo array (scoresSingle), então procuramos após o primeiro
                size_t posEndFirstArray = resposta.find(']', endNome);
                std::vector<double> scoresSingleVec;
                if (posEndFirstArray != std::string::npos) {
                     scoresSingleVec = ExtrairArrayDouble(resposta, posEndFirstArray);
                }

                bool existe = false;
                for (size_t k = 1; k < pcsCadastrados.size(); ++k) {
                    if (pcsCadastrados[k].nome == wNome) {
                        existe = true;
                        bool atualizou = false;
                        
                        // Só atualiza se o novo score for MAIOR que o salvo
                        if (totalMulti > pcsCadastrados[k].totalMultiCore && !scoresMultiVec.empty()) {
                            pcsCadastrados[k].totalMultiCore = totalMulti;
                            for (int s = 0; s < 100 && s < (int)scoresMultiVec.size(); ++s) 
                                pcsCadastrados[k].scoresMultiCore[s] = scoresMultiVec[s];
                            atualizou = true;
                        }
                        if (totalSingle > pcsCadastrados[k].totalSingleCore && !scoresSingleVec.empty()) {
                            pcsCadastrados[k].totalSingleCore = totalSingle;
                            for (int s = 0; s < 100 && s < (int)scoresSingleVec.size(); ++s) 
                                pcsCadastrados[k].scoresSingleCore[s] = scoresSingleVec[s];
                            atualizou = true;
                        }
                        if (atualizou) pcsCadastrados[k].numThreads = threads;
                        break;
                    }
                }
                
                if (!existe) {
                    PCReferencia novo;
                    novo.nome = wNome;
                    novo.totalMultiCore = totalMulti;
                    novo.totalSingleCore = totalSingle;
                    novo.numThreads = threads;
                    
                    // Preenche arrays com segurança
                    for(int s=0; s<100; ++s) {
                        novo.scoresMultiCore[s] = (s < (int)scoresMultiVec.size()) ? scoresMultiVec[s] : 0.0;
                        novo.scoresSingleCore[s] = (s < (int)scoresSingleVec.size()) ? scoresSingleVec[s] : 0.0;
                    }
                    pcsCadastrados.push_back(novo);
                }
                pos = endNome + 1;
            }
        }
    }
    InternetCloseHandle(hInternet);
}

double calcularScoreNormalizado(long long totalOps, double tempoSegundos, double fatorEscala) {
    if (tempoSegundos <= 0) return 0;
    double opsPorSegundo = static_cast<double>(totalOps) / tempoSegundos;
    return (opsPorSegundo / fatorEscala) / 100.0;
}

// === 100 FUNÇÕES DE BENCHMARK ===
long long benchmarkPontoFlutuante(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; double resultado = 0.0; while (true) { for (int i = 1; i <= 1000; ++i) resultado += std::sin(i) * std::cos(i) + std::sqrt(i); iteracoes += 1000; if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMatrizInteiros(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int tamanho = 128; std::vector<int> matA(tamanho*tamanho,3), matB(tamanho*tamanho,5), matC(tamanho*tamanho,0); while(true){ for(int i=0;i<tamanho;++i) for(int j=0;j<tamanho;++j){ int soma=0; for(int k=0;k<tamanho;++k) soma+=matA[i*tamanho+k]*matB[k*tamanho+j]; matC[i*tamanho+j]=soma; } iteracoes+=(tamanho*tamanho); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkOrdenacao(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::mt19937 rng(1337); std::vector<int> dados(10000); while(true){ std::generate(dados.begin(),dados.end(),[&rng](){return rng()%100000;}); std::sort(dados.begin(),dados.end()); iteracoes+=dados.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkPrimos(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0, numero = 500000; while(true){ bool ehPrimo=true; for(long long i=2;i<=std::sqrt(numero);++i){ if(numero%i==0){ehPrimo=false;break;} } iteracoes++;numero++;if(numero>900000)numero=500000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkAlocacaoMemoria(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true){ {std::vector<double> bloco(2048,3.14);volatile double val=bloco[1024];(void)val;} iteracoes+=2048; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkBitwise(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; unsigned int val = 0x12345678; while(true){ for(int i=0;i<1000;++i){val^=(val<<13);val^=(val>>17);val^=(val<<5);} iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkHashSimulado(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; unsigned long long hash = 5381; char texto[]="BenchmarkMassivoMultiThread"; while(true){ for(int i=0;i<sizeof(texto)-1;++i) hash=((hash<<5)+hash)+texto[i]; iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkCacheStress(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int tamanhoBuffer = 65536; std::vector<int> buffer(tamanhoBuffer,1); while(true){ for(int i=0;i<tamanhoBuffer;i+=7) buffer[(i*31)%tamanhoBuffer]+=i; iteracoes+=tamanhoBuffer; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkPolinomios(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; double x = 1.0001; while(true){ for(int i=0;i<500;++i){x=x*x+2.0*x+1.0;if(x>1e10)x=1.0001;} iteracoes+=500; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkLogicaArray(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<bool> flags(2048,false); while(true){ for(size_t i=0;i<flags.size();++i){flags[i]=!flags[i];if(i>0)flags[i]=flags[i]^flags[i-1];} iteracoes+=flags.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkCriptografia(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; uint32_t h0=0x6a09e667,h1=0xbb67ae85,h2=0x3c6ef372,h3=0xa54ff53a; while(true){ for(int i=0;i<100;++i){ uint32_t s0=(h0>>2|h0<<30)^(h0>>13|h0<<19)^(h0>>22|h0<<10); uint32_t s1=(h1>>6|h1<<26)^(h1>>11|h1<<21)^(h1>>25|h1<<7); h3=h2;h2=h1;h1=h0;h0=s0+s1+h3+i; } iteracoes+=100; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkCompressao(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<char> data(1024,'A'); while(true){ int count=1; for(size_t i=1;i<data.size();++i){ if(data[i]==data[i-1])count++;else count=1; } iteracoes+=data.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkFisica(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; struct Body{double x,y,vx,vy;}; std::vector<Body> bodies(50); for(auto&b:bodies){b.x=rand()%100;b.y=rand()%100;b.vx=1;b.vy=1;} while(true){ for(auto&b:bodies){ b.x+=b.vx;b.y+=b.vy; if(b.x>100||b.x<0)b.vx*=-1; if(b.y>100||b.y<0)b.vy*=-1; } iteracoes+=bodies.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkGameOfLife(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int width = 100; const int height = 100; std::vector<std::vector<bool>> grid(width, std::vector<bool>(height, false)); std::vector<std::vector<bool>> nextGrid(width, std::vector<bool>(height, false)); std::mt19937 rng(42); for(int x=0; x<width; ++x) for(int y=0; y<height; ++y) grid[x][y] = (rng() % 2 == 0); while (true) { for(int x=1; x<width-1; ++x) { for(int y=1; y<height-1; ++y) { int neighbors = 0; for(int dx=-1; dx<=1; ++dx) { for(int dy=-1; dy<=1; ++dy) { if(dx==0 && dy==0) continue; if(grid[x+dx][y+dy]) neighbors++; } } if(grid[x][y]) { nextGrid[x][y] = (neighbors == 2 || neighbors == 3); } else { nextGrid[x][y] = (neighbors == 3); } } } std::swap(grid, nextGrid); iteracoes += (width * height); if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkAudio(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; double phase = 0.0; while(true){ for(int i=0;i<4410;++i){ phase+=440.0/44100.0; if(phase>1.0)phase-=1.0; volatile double sample=std::sin(phase*2.0*3.14159); } iteracoes+=4410; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkRede(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> packet(1500,0xFF); while(true){ uint32_t checksum=0; for(size_t i=0;i<packet.size();i+=2){ checksum+=(packet[i]<<8)|packet[i+1]; } iteracoes+=packet.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkIA(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; double weights[10]={0.5}; double inputs[10]={1.0}; while(true){ double sum=0; for(int i=0;i<10;++i)sum+=weights[i]*inputs[i]; double output=1.0/(1.0+std::exp(-sum)); for(int i=0;i<10;++i)weights[i]+=0.001*output; iteracoes+=10; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkDatabase(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> index(10000); std::iota(index.begin(),index.end(),0); while(true){ int target=rand()%10000; bool found=std::binary_search(index.begin(),index.end(),target); iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkParticulas(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; struct Particle{float x,y,life;}; std::vector<Particle> parts(1000); while(true){ for(auto&p:parts){ p.x+=0.1;p.y+=0.1;p.life-=0.01; if(p.life<=0){p.life=1.0;p.x=0;p.y=0;} } iteracoes+=parts.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkSteganografia(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> image(4096,128); std::vector<uint8_t> secret(512,1); while(true){ for(size_t i=0;i<secret.size();++i){ image[i]=(image[i]&0xFE)|(secret[i]&1); } iteracoes+=secret.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkMandelbrot(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true){ for(int y=-100; y<=100; ++y) for(int x=-100; x<=100; ++x) { double zx=0, zy=0; double cx=x/50.0, cy=y/50.0; int i=0; for(; i<100 && (zx*zx+zy*zy)<4.0; ++i) { double tmp=zx*zx-zy*zy+cx; zy=2.0*zx*zy+cy; zx=tmp; } iteracoes+=i; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkFourier(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> signal(1024, 0.0); std::mt19937 rng(99); for(auto& s : signal) s = (rng()%1000)/1000.0; while(true){ for(int k=0; k<1024; ++k) { double real=0, imag=0; for(int n=0; n<1024; ++n) { double angle = 2.0 * 3.14159 * k * n / 1024; real += signal[n] * std::cos(angle); imag -= signal[n] * std::sin(angle); } } iteracoes+=1024*1024; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkShortestPath(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int V = 100; std::vector<std::vector<int>> graph(V, std::vector<int>(V, 999)); std::mt19937 rng(77); for(int i=0; i<V; ++i) for(int j=0; j<V; ++j) if(i!=j) graph[i][j] = rng()%100; while(true){ std::vector<int> dist(V, 999999); std::vector<bool> visited(V, false); dist[0]=0; for(int count=0; count<V-1; ++count) { int u=-1; for(int v=0; v<V; ++v) if(!visited[v] && (u==-1 || dist[v]<dist[u])) u=v; if(dist[u]==999999) break; visited[u]=true; for(int v=0; v<V; ++v) if(!visited[v] && graph[u][v]!=999 && dist[u]+graph[u][v]<dist[v]) dist[v]=dist[u]+graph[u][v]; } iteracoes+=V*V; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkRegex(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string text = "abc123def456ghi789jkl012mno345pqr678stu901vwx234yz"; while(true){ for(int i=0; i<10000; ++i) { bool match = false; for(size_t j=0; j<=text.size()-3; ++j) { if(std::isdigit(text[j]) && std::isdigit(text[j+1]) && std::isdigit(text[j+2])) { match=true; break; } } if(match) iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkXML(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string xml = "<root><item id='1'><name>Test</name></item></root>"; while(true){ size_t pos = 0; while((pos = xml.find('<', pos)) != std::string::npos) { size_t end = xml.find('>', pos); if(end == std::string::npos) break; pos = end + 1; iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-inicio).count()>=duracao) break; } return iteracoes; }
long long benchmarkMultiplicacaoMatriz(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int N = 200; std::vector<std::vector<double>> A(N, std::vector<double>(N, 1.5)); std::vector<std::vector<double>> B(N, std::vector<double>(N, 2.0)); std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0)); while(true) { for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) for(int k = 0; k < N; ++k) C[i][j] += A[i][k] * B[k][j]; iteracoes += N * N * N; for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) C[i][j] = 0.0; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkRayTracing(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; struct Sphere { double x, y, z, r; }; std::vector<Sphere> spheres = {{0, 0, 5, 1}, {2, 1, 6, 1.5}, {-2, -1, 7, 1.2}}; while(true) { for(int py = 0; py < 100; ++py) { for(int px = 0; px < 100; ++px) { double rayX = (px - 50) / 50.0; double rayY = (py - 50) / 50.0; double rayZ = 1.0; for(auto& sphere : spheres) { double a = rayX*rayX + rayY*rayY + rayZ*rayZ; double b = 2*(rayX*(-sphere.x) + rayY*(-sphere.y) + rayZ*(-sphere.z)); double c = sphere.x*sphere.x + sphere.y*sphere.y + sphere.z*sphere.z - sphere.r*sphere.r; double disc = b*b - 4*a*c; if(disc >= 0) iteracoes++; } } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkGenetico(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int POP_SIZE = 100; const int GENES = 50; std::mt19937 rng(12345); std::vector<std::vector<int>> population(POP_SIZE, std::vector<int>(GENES)); for(auto& ind : population) for(auto& gene : ind) gene = rng() % 2; while(true) { for(auto& ind : population) { int fitness = 0; for(int g : ind) fitness += g; iteracoes++; } for(int i = 0; i < POP_SIZE/2; ++i) { int crossPoint = rng() % GENES; for(int j = crossPoint; j < GENES; ++j) std::swap(population[i][j], population[POP_SIZE-1-i][j]); } for(auto& ind : population) { if(rng() % 100 < 5) { int pos = rng() % GENES; ind[pos] = !ind[pos]; } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkFluidos(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int GRID = 64; std::vector<std::vector<double>> density(GRID, std::vector<double>(GRID, 1.0)); std::vector<std::vector<double>> newDensity(GRID, std::vector<double>(GRID, 0.0)); while(true) { for(int i = 1; i < GRID-1; ++i) { for(int j = 1; j < GRID-1; ++j) { newDensity[i][j] = (density[i][j] + density[i-1][j] + density[i+1][j] + density[i][j-1] + density[i][j+1]) / 5.0; } } std::swap(density, newDensity); iteracoes += GRID * GRID; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkAESSimulado(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> block(16, 0xAA); std::vector<uint8_t> key(16, 0xBB); while(true) { for(int round = 0; round < 10; ++round) { for(int i = 0; i < 16; ++i) block[i] = (block[i] << 3) ^ (block[i] >> 5) ^ key[i]; std::rotate(block.begin(), block.begin() + (round % 4), block.end()); for(int i = 0; i < 12; ++i) block[i] ^= block[i+1] ^ block[i+2]; for(int i = 0; i < 16; ++i) block[i] ^= key[i]; } iteracoes += 16; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkAStar(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int GRID = 50; std::mt19937 rng(54321); while(true) { std::vector<std::vector<bool>> walkable(GRID, std::vector<bool>(GRID, true)); for(int i = 0; i < GRID*GRID/4; ++i) walkable[rng()%GRID][rng()%GRID] = false; std::vector<std::vector<int>> dist(GRID, std::vector<int>(GRID, -1)); std::queue<std::pair<int,int>> q; dist[0][0] = 0; q.push({0, 0}); int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; while(!q.empty()) { auto curr = q.front(); q.pop(); int x = curr.first; int y = curr.second; iteracoes++; for(auto& d : dirs) { int nx = x + d[0]; int ny = y + d[1]; if(nx >= 0 && nx < GRID && ny >= 0 && ny < GRID && walkable[nx][ny] && dist[nx][ny] == -1) { dist[nx][ny] = dist[x][y] + 1; q.push({nx, ny}); } } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMonteCarlo(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; long long inside = 0; std::mt19937 rng(98765); std::uniform_real_distribution<double> dist(0.0, 1.0); while(true) { for(int i = 0; i < 10000; ++i) { double x = dist(rng); double y = dist(rng); if(x*x + y*y <= 1.0) inside++; iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkConvolucao(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int IMG_W = 128, IMG_H = 128; const int KERNEL = 3; std::vector<std::vector<double>> image(IMG_H, std::vector<double>(IMG_W, 0.5)); std::vector<std::vector<double>> result(IMG_H, std::vector<double>(IMG_W, 0.0)); std::vector<std::vector<double>> kernel = {{1,2,1},{2,4,2},{1,2,1}}; while(true) { for(int y = 1; y < IMG_H-1; ++y) { for(int x = 1; x < IMG_W-1; ++x) { double sum = 0; for(int ky = 0; ky < KERNEL; ++ky) { for(int kx = 0; kx < KERNEL; ++kx) { sum += image[y+ky-1][x+kx-1] * kernel[ky][kx]; } } result[y][x] = sum / 16.0; } } iteracoes += (IMG_H-2) * (IMG_W-2) * KERNEL * KERNEL; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkBTree(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::map<int, int> btree; std::mt19937 rng(11111); while(true) { for(int i = 0; i < 1000; ++i) { btree[rng() % 100000] = rng(); iteracoes++; } for(int i = 0; i < 500; ++i) { auto it = btree.find(rng() % 100000); if(it != btree.end()) iteracoes++; } for(int i = 0; i < 100; ++i) { auto it = btree.find(rng() % 100000); if(it != btree.end()) { btree.erase(it); iteracoes++; } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkTensor(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int DIM = 20; std::vector<std::vector<std::vector<double>>> tensorA(DIM, std::vector<std::vector<double>>(DIM, std::vector<double>(DIM, 1.0))); std::vector<std::vector<std::vector<double>>> tensorB(DIM, std::vector<std::vector<double>>(DIM, std::vector<double>(DIM, 2.0))); std::vector<std::vector<std::vector<double>>> result(DIM, std::vector<std::vector<double>>(DIM, std::vector<double>(DIM, 0.0))); while(true) { for(int i = 0; i < DIM; ++i) for(int j = 0; j < DIM; ++j) for(int k = 0; k < DIM; ++k) result[i][j][k] = tensorA[i][j][k] * tensorB[i][j][k]; iteracoes += DIM * DIM * DIM; for(int i = 0; i < DIM; ++i) for(int j = 0; j < DIM; ++j) for(int k = 0; k < DIM; ++k) result[i][j][k] = 0.0; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkFatorial(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { long long res = 1; for(int i=1; i<=20; ++i) res *= i; iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 20; }
long long benchmarkFibonacci(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { long long a=0, b=1; for(int i=0; i<100; ++i) { long long temp = a+b; a=b; b=temp; } iteracoes+=100; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkHanoi(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; auto hanoi = [&](auto self, int n, int from, int to, int aux) -> void { if(n==1) { iteracoes++; return; } self(self, n-1, from, aux, to); iteracoes++; self(self, n-1, aux, to, from); }; while(true) { hanoi(hanoi, 15, 1, 3, 2); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkCrivo(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int N = 100000; std::vector<bool> is_prime(N, true); while(true) { std::fill(is_prime.begin(), is_prime.end(), true); is_prime[0]=is_prime[1]=false; for(int i=2; i*i<N; ++i) if(is_prime[i]) for(int j=i*i; j<N; j+=i) is_prime[j]=false; iteracoes+=N; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMDC(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::mt19937 rng(1); while(true) { for(int i=0; i<10000; ++i) { long long a = rng()%1000000, b = rng()%1000000; while(b) { long long t=b; b=a%b; a=t; } iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkPotenciaMod(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { long long base=2, exp=100000, mod=1000000007; long long res=1; base%=mod; while(exp>0) { if(exp%2==1) res=(res*base)%mod; exp>>=1; base=(base*base)%mod; } iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 100; }
long long benchmarkRaizNewton(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { double x = 2.0; for(int i=0; i<1000; ++i) x = 0.5 * (x + 10.0/x); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkSenoTaylor(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { double x = 1.0; double term = x; double sum = x; for(int n=1; n<20; ++n) { term *= -x*x / ((2*n)*(2*n+1)); sum += term; } iteracoes+=20; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkExpMath(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { double res = std::exp(1.0); (void)res; iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 1000; }
long long benchmarkLogNat(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { double res = std::log(2.71828); (void)res; iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 1000; }
long long benchmarkAbsBulk(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> v(10000, -5.5); while(true) { for(auto& x : v) x = std::abs(x); iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkRoundBulk(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> v(10000, 3.14159); while(true) { for(auto& x : v) x = std::round(x); iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkClamp(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::mt19937 rng(1); while(true) { for(int i=0; i<10000; ++i) { double val = rng()%1000; double c = std::max(0.0, std::min(100.0, val)); (void)c; } iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkLerp(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { for(int i=0; i<10000; ++i) { double t = (double)i/10000.0; double res = 0.0 + t * (100.0 - 0.0); (void)res; } iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkSpline(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { for(double t=0; t<1.0; t+=0.01) { double res = 2*t*t*t - 3*t*t + 1; (void)res; iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkBubbleSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(500); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); for(size_t i=0; i<v.size(); ++i) for(size_t j=0; j<v.size()-1; ++j) if(v[j]>v[j+1]) std::swap(v[j], v[j+1]); iteracoes+=v.size()*v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkInsertionSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(1000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); for(size_t i=1; i<v.size(); ++i) { int key=v[i]; int j=i-1; while(j>=0 && v[j]>key) { v[j+1]=v[j]; j--; } v[j+1]=key; } iteracoes+=v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkSelectionSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(800); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); for(size_t i=0; i<v.size(); ++i) { size_t min_idx=i; for(size_t j=i+1; j<v.size(); ++j) if(v[j]<v[min_idx]) min_idx=j; std::swap(v[i], v[min_idx]); } iteracoes+=v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkQuickSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(2000); std::mt19937 rng(1); auto qs = [&](auto self, int l, int r, std::vector<int>& arr) -> void { if(l<r) { int p=arr[l+(r-l)/2]; int i=l, j=r; while(i<=j) { while(arr[i]<p) i++; while(arr[j]>p) j--; if(i<=j) { std::swap(arr[i], arr[j]); i++; j--; } iteracoes++; } self(self, l, j, arr); self(self, i, r, arr); } }; while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); qs(qs, 0, v.size()-1, v); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMergeSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(2000); std::mt19937 rng(1); auto ms = [&](auto self, std::vector<int>& arr) -> void { if(arr.size()<=1) return; int mid=arr.size()/2; std::vector<int> left(arr.begin(), arr.begin()+mid); std::vector<int> right(arr.begin()+mid, arr.end()); self(self, left); self(self, right); size_t i=0, j=0, k=0; while(i<left.size() && j<right.size()) { if(left[i]<=right[j]) arr[k++]=left[i++]; else arr[k++]=right[j++]; iteracoes++; } while(i<left.size()) arr[k++]=left[i++]; while(j<right.size()) arr[k++]=right[j++]; }; while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); ms(ms, v); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkHeapSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(2000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); std::make_heap(v.begin(), v.end()); std::sort_heap(v.begin(), v.end()); iteracoes+=v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkCountingSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(5000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%100;}); std::vector<int> count(100,0); for(int x:v) count[x]++; iteracoes+=v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkRadixSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(2000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%100000;}); int maxVal = *std::max_element(v.begin(), v.end()); for(int exp=1; maxVal/exp>0; exp*=10) { std::vector<int> output(v.size()); std::vector<int> count(10,0); for(int i=0; i<v.size(); i++) count[(v[i]/exp)%10]++; for(int i=1; i<10; i++) count[i]+=count[i-1]; for(int i=v.size()-1; i>=0; i--) { output[count[(v[i]/exp)%10]-1]=v[i]; count[(v[i]/exp)%10]--; } for(int i=0; i<v.size(); i++) v[i]=output[i]; iteracoes+=v.size(); } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkBucketSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> v(2000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return (double)(rng()%1000)/1000.0;}); int n=v.size(); std::vector<std::vector<double>> buckets(n); for(int i=0; i<n; i++) { int bi = n*v[i]; buckets[bi].push_back(v[i]); } for(int i=0; i<n; i++) std::sort(buckets[i].begin(), buckets[i].end()); iteracoes+=v.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkShellSort(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(2000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng()%1000;}); int n=v.size(); for(int gap=n/2; gap>0; gap/=2) { for(int i=gap; i<n; i++) { int temp=v[i]; int j; for(j=i; j>=gap && v[j-gap]>temp; j-=gap) { v[j]=v[j-gap]; iteracoes++; } v[j]=temp; } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrCopy(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string src(1000, 'A'); std::string dst; while(true) { dst = src; iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrConcat(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s; while(true) { s.clear(); for(int i=0; i<100; ++i) s += "ABC"; iteracoes+=100; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrCmp(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s1(1000, 'A'), s2(1000, 'A'); while(true) { volatile bool res = (s1 == s2); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrFind(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(10000, 'A'); s[5000]='B'; while(true) { size_t pos = s.find('B'); (void)pos; iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrRev(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(1000, 'A'); while(true) { std::reverse(s.begin(), s.end()); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrUpper(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(1000, 'a'); while(true) { std::transform(s.begin(), s.end(), s.begin(), ::toupper); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStrTrim(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s = "   Hello World   "; while(true) { s.erase(0, s.find_first_not_of(' ')); s.erase(s.find_last_not_of(' ')+1); iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 1000; }
long long benchmarkCSVParse(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string csv = "1,2,3,4,5,6,7,8,9,10"; while(true) { std::stringstream ss(csv); std::string item; while(std::getline(ss, item, ',')) { iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkJSONToken(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string json = "{\"key\":\"value\",\"num\":123}"; while(true) { for(char c : json) { if(c=='{' || c=='}' || c==':' || c==',') iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 100; }
long long benchmarkBase64Enc(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string input = "Hello World Benchmark"; while(true) { std::string out; int val=0, valb=-6; for(unsigned char c : input) { val=(val<<8)+c; valb+=8; while(valb>=0) { out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]); valb-=6; } } iteracoes+=input.size(); if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkHexDump(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> data(1000, 0xFF); while(true) { std::stringstream ss; for(uint8_t b : data) { ss << std::hex << std::setw(2) << std::setfill('0') << (int)b; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkCRC32(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> data(1000, 1); while(true) { uint32_t crc = 0xFFFFFFFF; for(uint8_t b : data) { crc ^= b; for(int i=0; i<8; i++) crc = (crc>>1) ^ (0xEDB88320 & (-(crc&1))); } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkAdler32(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> data(1000, 1); while(true) { uint32_t a=1, b=0; for(uint8_t d : data) { a = (a+d) % 65521; b = (b+a) % 65521; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkFletcher(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> data(1000, 1); while(true) { uint16_t sum1=0, sum2=0; for(uint8_t d : data) { sum1 = (sum1+d) % 255; sum2 = (sum2+sum1) % 255; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkXORCipher(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<uint8_t> data(1000, 1); uint8_t key = 0xAA; while(true) { for(auto& d : data) d ^= key; iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkROT13(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(1000, 'A'); while(true) { for(auto& c : s) { if(c>='A' && c<='Z') c = 'A' + (c-'A'+13)%26; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkCaesar(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(1000, 'A'); int shift = 3; while(true) { for(auto& c : s) { if(c>='A' && c<='Z') c = 'A' + (c-'A'+shift)%26; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkVigenere(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s(1000, 'A'); std::string key = "KEY"; while(true) { for(size_t i=0; i<s.size(); ++i) { char k = key[i%key.size()]; if(s[i]>='A' && s[i]<='Z') s[i] = 'A' + (s[i]-'A'+k-'A')%26; } iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkRandomFill(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(10000); std::mt19937 rng(1); while(true) { std::generate(v.begin(), v.end(), [&rng](){return rng();}); iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMemSet(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(10000); while(true) { memset(v.data(), 0, v.size()*sizeof(int)); iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMemMove(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<int> v(10000, 1); std::vector<int> dst(10000); while(true) { memcpy(dst.data(), v.data(), v.size()*sizeof(int)); iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkVecAdd(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> a(10000, 1.0), b(10000, 2.0), c(10000); while(true) { for(size_t i=0; i<a.size(); ++i) c[i]=a[i]+b[i]; iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkVecDot(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::vector<double> a(10000, 1.0), b(10000, 2.0); while(true) { double res=0; for(size_t i=0; i<a.size(); ++i) res+=a[i]*b[i]; iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkVecCross(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; while(true) { for(int i=0; i<10000; ++i) { double ax=1,ay=2,az=3, bx=4,by=5,bz=6; double cx=ay*bz-az*by, cy=az*bx-ax*bz, cz=ax*by-ay*bx; (void)cx; (void)cy; (void)cz; } iteracoes+=10000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkMatDet(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int N=10; std::vector<std::vector<double>> m(N, std::vector<double>(N, 1.5)); while(true) { double det=1; for(int i=0; i<N; ++i) { for(int j=i+1; j<N; ++j) { double factor=m[j][i]/m[i][i]; for(int k=i; k<N; ++k) m[j][k]-=factor*m[i][k]; } det*=m[i][i]; } iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 100; }
long long benchmarkMatInv(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int N=5; std::vector<std::vector<double>> m(N, std::vector<double>(N, 0)); for(int i=0;i<N;++i) m[i][i]=1.0; while(true) { double det=1; for(int i=0; i<N; ++i) { for(int j=i+1; j<N; ++j) { double factor=m[j][i]/m[i][i]; for(int k=i; k<N; ++k) m[j][k]-=factor*m[i][k]; } det*=m[i][i]; } iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes * 100; }
long long benchmarkLLTraverse(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; struct Node { int val; Node* next; }; Node* head = nullptr; for(int i=0; i<1000; ++i) { Node* n = new Node{i, head}; head = n; } while(true) { Node* curr = head; while(curr) { iteracoes++; curr=curr->next; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkBST(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::set<int> bst; std::mt19937 rng(1); while(true) { for(int i=0; i<1000; ++i) bst.insert(rng()%100000); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkHashMap(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::unordered_map<int, int> hm; std::mt19937 rng(1); while(true) { for(int i=0; i<1000; ++i) hm[rng()%100000] = i; iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkPriorityQ(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::priority_queue<int> pq; std::mt19937 rng(1); while(true) { for(int i=0; i<1000; ++i) pq.push(rng()%100000); for(int i=0; i<1000; ++i) if(!pq.empty()) pq.pop(); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkStack(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::stack<int> st; while(true) { for(int i=0; i<1000; ++i) st.push(i); for(int i=0; i<1000; ++i) if(!st.empty()) st.pop(); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkQueue(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::queue<int> q; while(true) { for(int i=0; i<1000; ++i) q.push(i); for(int i=0; i<1000; ++i) if(!q.empty()) q.pop(); iteracoes+=1000; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkDFS(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int V=100; std::vector<std::vector<int>> adj(V); std::mt19937 rng(1); for(int i=0; i<V; ++i) for(int j=0; j<5; ++j) adj[i].push_back(rng()%V); while(true) { std::vector<bool> visited(V, false); std::stack<int> stk; stk.push(0); while(!stk.empty()) { int u=stk.top(); stk.pop(); if(!visited[u]) { visited[u]=true; iteracoes++; for(int v : adj[u]) if(!visited[v]) stk.push(v); } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkBFS(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int V=100; std::vector<std::vector<int>> adj(V); std::mt19937 rng(1); for(int i=0; i<V; ++i) for(int j=0; j<5; ++j) adj[i].push_back(rng()%V); while(true) { std::vector<bool> visited(V, false); std::queue<int> q; q.push(0); visited[0]=true; while(!q.empty()) { int u=q.front(); q.pop(); iteracoes++; for(int v : adj[u]) if(!visited[v]) { visited[v]=true; q.push(v); } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkDijkstra(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int V=50; std::vector<std::vector<std::pair<int,int>>> adj(V); std::mt19937 rng(1); for(int i=0; i<V; ++i) for(int j=0; j<5; ++j) adj[i].push_back({rng()%V, rng()%100}); while(true) { std::vector<int> dist(V, INT_MAX); std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq; dist[0]=0; pq.push({0,0}); while(!pq.empty()) { int u=pq.top().second; pq.pop(); for(auto& edge : adj[u]) { int v=edge.first, w=edge.second; if(dist[u]+w < dist[v]) { dist[v]=dist[u]+w; pq.push({dist[v], v}); iteracoes++; } } } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkFloyd(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int V=50; std::vector<std::vector<int>> dist(V, std::vector<int>(V, 999)); std::mt19937 rng(1); for(int i=0; i<V; ++i) for(int j=0; j<V; ++j) if(i!=j) dist[i][j]=rng()%100; while(true) { for(int k=0; k<V; ++k) for(int i=0; i<V; ++i) for(int j=0; j<V; ++j) if(dist[i][j] > dist[i][k]+dist[k][j]) dist[i][j]=dist[i][k]+dist[k][j]; iteracoes+=V*V*V; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkKnapsack(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; const int N=100, W=100; std::vector<int> wt(N, 1), val(N, 1); std::vector<std::vector<int>> K(N+1, std::vector<int>(W+1, 0)); while(true) { for(int i=0; i<=N; ++i) for(int w=0; w<=W; ++w) { if(i==0||w==0) K[i][w]=0; else if(wt[i-1]<=w) K[i][w]=std::max(val[i-1]+K[i-1][w-wt[i-1]], K[i-1][w]); else K[i][w]=K[i-1][w]; iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkLCS(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string X="ABCBDAB", Y="BDCABA"; int m=X.size(), n=Y.size(); std::vector<std::vector<int>> L(m+1, std::vector<int>(n+1, 0)); while(true) { for(int i=0; i<=m; ++i) for(int j=0; j<=n; ++j) { if(i==0||j==0) L[i][j]=0; else if(X[i-1]==Y[j-1]) L[i][j]=L[i-1][j-1]+1; else L[i][j]=std::max(L[i-1][j], L[i][j-1]); iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkEditDist(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::string s1="kitten", s2="sitting"; int m=s1.size(), n=s2.size(); std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, 0)); while(true) { for(int i=0; i<=m; ++i) for(int j=0; j<=n; ++j) { if(i==0) dp[i][j]=j; else if(j==0) dp[i][j]=i; else if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]; else dp[i][j]=1+std::min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}); iteracoes++; } if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }
long long benchmarkPrimeFact(int duracao) { auto inicio = std::chrono::high_resolution_clock::now(); long long iteracoes = 0; std::mt19937 rng(1); while(true) { long long n = rng()%1000000; for(long long i=2; i*i<=n; ++i) { while(n%i==0) { n/=i; iteracoes++; } } if(n>1) iteracoes++; if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - inicio).count() >= duracao) break; } return iteracoes; }

template <typename Func>
double rodarMultiThread(Func func, int numThreads, int duracao, double fatorEscala) {
    auto inicioTotal = std::chrono::high_resolution_clock::now();
    std::vector<std::future<long long>> futuros;
    for (int t = 0; t < numThreads; ++t) futuros.push_back(std::async(std::launch::async, func, duracao));
    long long total = 0;
    for (auto& f : futuros) total += f.get();
    auto fimTotal = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempoTotal = fimTotal - inicioTotal;
    return calcularScoreNormalizado(total, tempoTotal.count(), fatorEscala);
}

template <typename Func>
double rodarSingleCore(Func func, int duracao, double fatorEscala) {
    return rodarMultiThread(func, 1, duracao, fatorEscala);
}

int MedirTextoLargura(HFONT fonte, const wchar_t* texto) {
    if (!fonte || !texto) return 0;
    HDC hdc = GetDC(NULL);
    HFONT antiga = (HFONT)SelectObject(hdc, fonte);
    SIZE sz;
    GetTextExtentPoint32W(hdc, texto, (int)wcslen(texto), &sz);
    SelectObject(hdc, antiga);
    ReleaseDC(NULL, hdc);
    return sz.cx;
}

void PosicionarControlesTopo() {
    if (!hStaticLang || !hFontAtual) return;
    double escala = currentFontSize / 14.0;
    int alturaCampo = (int)(25 * escala);
    int alturaBtn = (int)(30 * escala);
    int padding = (int)(16 * escala);
    int espLabel = (int)(6 * escala);
    int espCampo = (int)(12 * escala);
    int alturaLinha = ((alturaCampo > alturaBtn) ? alturaCampo : alturaBtn) + (int)(8 * escala);
    int x = 15, y = 15;
    int limiteDireita = g_winW - 15;
    
    int wComboLang = (int)(150 * escala);
    int wComboFont = (int)(90 * escala);
    int wComboCompare = (int)(280 * escala);
    
    auto colocarPar = [&](HWND lbl, HWND ctrl, const wchar_t* texto, int larguraCtrl) {
        int wLbl = MedirTextoLargura(hFontAtual, texto) + padding;
        int totalNecessario = wLbl + espLabel + larguraCtrl + espCampo;
        if (x + totalNecessario > limiteDireita && x > 15) {
            x = 15;
            y += alturaLinha;
        }
        if (lbl) MoveWindow(lbl, x, y, wLbl, alturaCampo, TRUE);
        x += wLbl + espLabel;
        if (ctrl) MoveWindow(ctrl, x, y, larguraCtrl, 250, TRUE);
        x += larguraCtrl + espCampo;
    };

    colocarPar(hStaticLang, hComboLang, traducoes[currentLangIndex].labelLang, wComboLang);
    colocarPar(hStaticFont, hComboFont, traducoes[currentLangIndex].labelFont, wComboFont);
    colocarPar(hStaticCompare, hComboCompare, traducoes[currentLangIndex].labelCompare, wComboCompare);
    
    int wBtn = MedirTextoLargura(hFontAtual, traducoes[currentLangIndex].btnRun) + (int)(30 * escala);
    int wBtnMin = (int)(90 * escala);
    if (wBtn < wBtnMin) wBtn = wBtnMin;
    
    if (x + wBtn > limiteDireita && x > 15) {
        x = 15;
        y += alturaLinha;
    }
    if (hBtnRun) MoveWindow(hBtnRun, x, y - (int)(2 * escala), wBtn, alturaBtn, TRUE);
    x += wBtn + espCampo;
    
    y += alturaLinha + (int)(4 * escala);
    if (hStaticStatus) MoveWindow(hStaticStatus, 15, y, g_winW - 30, alturaCampo, TRUE);
    y += alturaCampo + (int)(15 * escala);
    
    int alturaLog = g_winH - y - 15;
    if (alturaLog < 100) alturaLog = 100;
    if (hEditLog) MoveWindow(hEditLog, 15, y, g_winW - 30, alturaLog, TRUE);
}

void AtualizarFontesSimples(int fontSize) {
    currentFontSize = fontSize;
    if (hFontAtual) DeleteObject(hFontAtual);
    hFontAtual = CreateFontW(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
    
    HWND controles[] = {hStaticLang, hComboLang, hStaticFont, hComboFont,
                        hStaticCompare, hComboCompare, hBtnRun, hStaticStatus};
    for (HWND h : controles) {
        if (h) SendMessageW(h, WM_SETFONT, (WPARAM)hFontAtual, TRUE);
    }
    
    if (hEditLog) {
        CHARFORMAT2W cf = {0};
        cf.cbSize = sizeof(cf);
        cf.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR;
        cf.yHeight = fontSize * 10;
        wcscpy_s(cf.szFaceName, L"Consolas");
        cf.crTextColor = RGB(0, 0, 0);
        SendMessageW(hEditLog, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
    }
    
    InvalidateRect(GetParent(hStaticLang), NULL, TRUE);
    PosicionarControlesTopo();
}

void AtualizarIdiomaInterface(int langIndex) {
    currentLangIndex = langIndex;
    SetWindowTextW(GetParent(hStaticLang), traducoes[langIndex].tituloJanela);
    SetWindowTextW(hStaticLang, traducoes[langIndex].labelLang);
    SetWindowTextW(hStaticCompare, traducoes[langIndex].labelCompare);
    SetWindowTextW(hStaticFont, traducoes[langIndex].labelFont);
    SetWindowTextW(hBtnRun, traducoes[langIndex].btnRun);
    
    if (GetWindowTextLengthW(hStaticStatus) > 0)
        SetWindowTextW(hStaticStatus, traducoes[langIndex].statusPronto);
        
    if (pcsCadastrados.size() > 0) 
        pcsCadastrados[0].nome = traducoes[langIndex].selecionePC;
        
    AtualizarListaComparacao();
    if (benchmarkRealizado) AtualizarPainelComparativo();
    PosicionarControlesTopo();
}

void AtualizarListaComparacao() {
    SendMessageW(hComboCompare, CB_RESETCONTENT, 0, 0);
    if (pcsCadastrados.empty()) return;

    std::vector<size_t> indices;
    for (size_t i = 1; i < pcsCadastrados.size(); ++i) indices.push_back(i);
    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        return pcsCadastrados[a].totalMultiCore > pcsCadastrados[b].totalMultiCore;
    });

    int pos = (int)SendMessageW(hComboCompare, CB_ADDSTRING, 0, (LPARAM)pcsCadastrados[0].nome.c_str());
    SendMessageW(hComboCompare, CB_SETITEMDATA, pos, (LPARAM)0);

    for (size_t idx : indices) {
        pos = (int)SendMessageW(hComboCompare, CB_ADDSTRING, 0, (LPARAM)pcsCadastrados[idx].nome.c_str());
        SendMessageW(hComboCompare, CB_SETITEMDATA, pos, (LPARAM)idx);
    }
    
    // Se houver itens, seleciona o primeiro (geralmente o próprio PC ou o melhor)
    if (pcsCadastrados.size() > 0)
        SendMessageW(hComboCompare, CB_SETCURSEL, 0, 0);
}

void AtualizarPainelComparativo() {
    if (!benchmarkRealizado) {
        SetWindowTextW(hEditLog, traducoes[currentLangIndex].avisoRodarPrimeiro);
        return;
    }
    
    int pos = (int)SendMessageW(hComboCompare, CB_GETCURSEL, 0, 0);
    int comboIndex = -1;
    if (pos >= 0) comboIndex = (int)SendMessageW(hComboCompare, CB_GETITEMDATA, pos, 0);
    bool temComparacao = (comboIndex > 0 && comboIndex < (int)pcsCadastrados.size());
    
    std::wstring logText = L"";
    logText += L"===============================================================\r\n";
    logText += traducoes[currentLangIndex].headerResult;
    logText += L"\r\n===============================================================\r\n\r\n";
    
    // MULTI-CORE SECTION
    logText += traducoes[currentLangIndex].compMultiCore;
    logText += L"\r\n";
    {
        wchar_t cabecalho[512];
        if (temComparacao) {
            swprintf_s(cabecalho, L"%-35s | %12s | %12s | %10s\r\n",
                       traducoes[currentLangIndex].colTeste, traducoes[currentLangIndex].colSeuPC,
                       traducoes[currentLangIndex].colOutroPC, traducoes[currentLangIndex].colDif);
        } else {
            swprintf_s(cabecalho, L"%-35s | %12s\r\n",
                       traducoes[currentLangIndex].colTeste, traducoes[currentLangIndex].colSeuPC);
        }
        logText += cabecalho;
    }
    logText += L"-----------------------------------------------------------------------\r\n";
    
    for (int i = 0; i < 100; ++i) {
        wchar_t linha[512];
        const wchar_t* nomeTeste = (traducoes[currentLangIndex].nomesTestes[0] != nullptr && traducoes[currentLangIndex].nomesTestes[0][0] != 0) ? 
                                   traducoes[currentLangIndex].nomesTestes[i] : 
                                   nomesTestesPT[i];
        
        if (temComparacao) {
            double diff = 0.0;
            if (pcsCadastrados[comboIndex].scoresMultiCore[i] > 0) {
                diff = ((meuUltimoScoreTestsMulti[i] - pcsCadastrados[comboIndex].scoresMultiCore[i]) /
                        pcsCadastrados[comboIndex].scoresMultiCore[i]) * 100.0;
            }
            swprintf_s(linha, L"%-35s | %12.1f | %12.1f | %9.1f%%\r\n",
                       nomeTeste,
                       meuUltimoScoreTestsMulti[i],
                       pcsCadastrados[comboIndex].scoresMultiCore[i],
                       diff);
        } else {
            swprintf_s(linha, L"%-35s | %12.1f\r\n",
                       nomeTeste,
                       meuUltimoScoreTestsMulti[i]);
        }
        logText += linha;
    }
    
    wchar_t total[256];
    double diffTotalMulti = 0.0;
    if (temComparacao) {
        if (pcsCadastrados[comboIndex].totalMultiCore > 0) {
            diffTotalMulti = ((meuUltimoTotalMulti - pcsCadastrados[comboIndex].totalMultiCore) /
                         pcsCadastrados[comboIndex].totalMultiCore) * 100.0;
        }
        swprintf_s(total, L"\r\n%s: %.1f PTS | %.1f PTS | %.1f%%\r\n", 
                   traducoes[currentLangIndex].compTotal, meuUltimoTotalMulti, 
                   pcsCadastrados[comboIndex].totalMultiCore, diffTotalMulti);
    } else {
        swprintf_s(total, L"\r\n%s: %.1f PTS\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalMulti);
    }
    logText += total;

    // SINGLE-CORE SECTION
    logText += L"\r\n";
    logText += traducoes[currentLangIndex].compSingleCore;
    logText += L"\r\n";
    {
        wchar_t cabecalho[512];
        if (temComparacao) {
            swprintf_s(cabecalho, L"%-35s | %12s | %12s | %10s\r\n",
                       traducoes[currentLangIndex].colTeste, traducoes[currentLangIndex].colSeuPC,
                       traducoes[currentLangIndex].colOutroPC, traducoes[currentLangIndex].colDif);
        } else {
            swprintf_s(cabecalho, L"%-35s | %12s\r\n",
                       traducoes[currentLangIndex].colTeste, traducoes[currentLangIndex].colSeuPC);
        }
        logText += cabecalho;
    }
    logText += L"-----------------------------------------------------------------------\r\n";
    
    for (int i = 0; i < 100; ++i) {
        wchar_t linha[512];
        const wchar_t* nomeTeste = (traducoes[currentLangIndex].nomesTestes[0] != nullptr && traducoes[currentLangIndex].nomesTestes[0][0] != 0) ? 
                                   traducoes[currentLangIndex].nomesTestes[i] : 
                                   nomesTestesPT[i];
        
        if (temComparacao) {
            double diff = 0.0;
            if (pcsCadastrados[comboIndex].scoresSingleCore[i] > 0) {
                diff = ((meuUltimoScoreTestsSingle[i] - pcsCadastrados[comboIndex].scoresSingleCore[i]) /
                        pcsCadastrados[comboIndex].scoresSingleCore[i]) * 100.0;
            }
            swprintf_s(linha, L"%-35s | %12.1f | %12.1f | %9.1f%%\r\n",
                       nomeTeste,
                       meuUltimoScoreTestsSingle[i],
                       pcsCadastrados[comboIndex].scoresSingleCore[i],
                       diff);
        } else {
            swprintf_s(linha, L"%-35s | %12.1f\r\n",
                       nomeTeste,
                       meuUltimoScoreTestsSingle[i]);
        }
        logText += linha;
    }
    
    double diffTotalSingle = 0.0;
    if (temComparacao) {
        if (pcsCadastrados[comboIndex].totalSingleCore > 0) {
            diffTotalSingle = ((meuUltimoTotalSingle - pcsCadastrados[comboIndex].totalSingleCore) /
                         pcsCadastrados[comboIndex].totalSingleCore) * 100.0;
        }
        swprintf_s(total, L"\r\n%s: %.1f PTS | %.1f PTS | %.1f%%\r\n", 
                   traducoes[currentLangIndex].compTotal, meuUltimoTotalSingle, 
                   pcsCadastrados[comboIndex].totalSingleCore, diffTotalSingle);
    } else {
        swprintf_s(total, L"\r\n%s: %.1f PTS\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalSingle);
    }
    logText += total;

    // DESTAQUE VISUAL GRANDE NO FINAL
    logText += L"\r\n=================================================================\r\n";
    if (temComparacao) {
        double diffFinal = diffTotalMulti; 
        
        if (diffFinal > 0) {
            logText += L"\r\n";
            logText += traducoes[currentLangIndex].msgMaisRapido;
            wchar_t buf[100];
            swprintf_s(buf, L"%.1f%%) ***\r\n", diffFinal);
            logText += buf;
        } else if (diffFinal < 0) {
            logText += L"\r\n";
            logText += traducoes[currentLangIndex].msgMaisLento;
            wchar_t buf[100];
            swprintf_s(buf, L"%.1f%%) ***\r\n", diffFinal);
            logText += buf;
        } else {
            logText += L"\r\n";
            logText += traducoes[currentLangIndex].msgEmpate;
            logText += L"\r\n";
        }
    } else {
        logText += L"\r\n";
        logText += traducoes[currentLangIndex].msgSelecioneParaComparar;
        logText += L"\r\n";
    }
    logText += L"=================================================================\r\n";

    SetWindowTextW(hEditLog, logText.c_str());
}

void ExecutarBenchmarkThread(HWND hwnd, int langIndex) {
    benchmarkEmAndamento = true;
    
    // Bloco try-catch para evitar que qualquer exceção não tratada feche o app
    try {
        EnableWindow(hBtnRun, FALSE);
        EnableWindow(hComboLang, FALSE);
        EnableWindow(hComboCompare, FALSE);
        EnableWindow(hComboFont, FALSE);
        
        // Desabilita o botão de fechar da janela
        HMENU hMenu = GetSystemMenu(hwnd, FALSE);
        if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

        unsigned int numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 4;
        
        long long (*testesFuncs[100])(int) = {
            benchmarkPontoFlutuante, benchmarkMatrizInteiros, benchmarkOrdenacao, benchmarkPrimos, benchmarkAlocacaoMemoria, benchmarkBitwise, benchmarkHashSimulado, benchmarkCacheStress, benchmarkPolinomios, benchmarkLogicaArray,
            benchmarkCriptografia, benchmarkCompressao, benchmarkFisica, benchmarkGameOfLife, benchmarkAudio, benchmarkRede, benchmarkIA, benchmarkDatabase, benchmarkParticulas, benchmarkSteganografia,
            benchmarkMandelbrot, benchmarkFourier, benchmarkShortestPath, benchmarkRegex, benchmarkXML, benchmarkMultiplicacaoMatriz, benchmarkRayTracing, benchmarkGenetico, benchmarkFluidos, benchmarkAESSimulado,
            benchmarkAStar, benchmarkMonteCarlo, benchmarkConvolucao, benchmarkBTree, benchmarkTensor, benchmarkFatorial, benchmarkFibonacci, benchmarkHanoi, benchmarkCrivo, benchmarkMDC,
            benchmarkPotenciaMod, benchmarkRaizNewton, benchmarkSenoTaylor, benchmarkExpMath, benchmarkLogNat, benchmarkAbsBulk, benchmarkRoundBulk, benchmarkClamp, benchmarkLerp, benchmarkSpline,
            benchmarkBubbleSort, benchmarkInsertionSort, benchmarkSelectionSort, benchmarkQuickSort, benchmarkMergeSort, benchmarkHeapSort, benchmarkCountingSort, benchmarkRadixSort, benchmarkBucketSort, benchmarkShellSort,
            benchmarkStrCopy, benchmarkStrConcat, benchmarkStrCmp, benchmarkStrFind, benchmarkStrRev, benchmarkStrUpper, benchmarkStrTrim, benchmarkCSVParse, benchmarkJSONToken, benchmarkBase64Enc,
            benchmarkHexDump, benchmarkCRC32, benchmarkAdler32, benchmarkFletcher, benchmarkXORCipher, benchmarkROT13, benchmarkCaesar, benchmarkVigenere, benchmarkRandomFill, benchmarkMemSet,
            benchmarkMemMove, benchmarkVecAdd, benchmarkVecDot, benchmarkVecCross, benchmarkMatDet, benchmarkMatInv, benchmarkLLTraverse, benchmarkBST, benchmarkHashMap, benchmarkPriorityQ,
            benchmarkStack, benchmarkQueue, benchmarkDFS, benchmarkBFS, benchmarkDijkstra, benchmarkFloyd, benchmarkKnapsack, benchmarkLCS, benchmarkEditDist, benchmarkPrimeFact
        };
        
        double fatoresEscala[100] = {
            500000.0, 50000.0, 200000.0, 10000.0, 800000.0, 1000000.0, 500000.0, 300000.0, 400000.0, 600000.0,
            200000.0, 300000.0, 150000.0, 100000.0, 400000.0, 500000.0, 250000.0, 10000.0, 200000.0, 300000.0,
            50000.0, 1000.0, 50000.0, 1000000.0, 500000.0, 10000.0, 5000.0, 50000.0, 200000.0, 100000.0,
            50000.0, 50000.0, 100000.0, 10000.0, 5000.0, 1000.0, 1000.0, 100.0, 100000.0, 10000.0,
            1000.0, 10000.0, 10000.0, 1000.0, 1000.0, 100000.0, 100000.0, 100000.0, 100000.0, 10000.0,
            10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0,
            100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0,
            100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0,
            100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0,
            100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0, 100000.0
        };
        
        int duracaoPorTeste = 1;
        
        meuUltimoTotalMulti = 0.0;
        meuUltimoTotalSingle = 0.0;
        meuUltimoNumThreads = numThreads;
        
        // FASE 1: MULTI-CORE (roda os 100 testes primeiro)
        SetWindowTextW(hStaticStatus, traducoes[langIndex].statusRodandoMulti);
        std::wstring logText = std::wstring(traducoes[langIndex].compMultiCore) + L" - " +
                               traducoes[langIndex].lblThreads + std::to_wstring(numThreads) + L"\r\n\r\n";
        {
            wchar_t cab[256];
            swprintf_s(cab, L"%-35s | %12s\r\n", traducoes[langIndex].colTeste, traducoes[langIndex].colPontuacao);
            logText += cab;
        }
        logText += L"-----------------------------------------------------------------------\r\n";
        SetWindowTextW(hEditLog, logText.c_str());
        
        for (int i = 0; i < 100; ++i) {
            double scoreMulti = rodarMultiThread(testesFuncs[i], numThreads, duracaoPorTeste, fatoresEscala[i]);
            meuUltimoScoreTestsMulti[i] = scoreMulti;
            meuUltimoTotalMulti += scoreMulti;
            
            wchar_t linha[256];
            swprintf_s(linha, L"%-35s | %12.1f\r\n", nomesTestesPT[i], scoreMulti);
            logText += linha;
            SetWindowTextW(hEditLog, logText.c_str());
            SendMessageW(hEditLog, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
            SendMessageW(hEditLog, EM_SCROLLCARET, 0, 0);
            
            wchar_t status[256];
            swprintf_s(status, L"%s %d/100", traducoes[langIndex].compMultiCore, i+1);
            SetWindowTextW(hStaticStatus, status);
        }
        
        // FASE 2: SINGLE-CORE (só começa depois que o multi-core termina)
        SetWindowTextW(hStaticStatus, traducoes[langIndex].statusRodandoSingle);
        logText += L"\r\n";
        logText += traducoes[langIndex].compSingleCore;
        logText += L"\r\n\r\n";
        {
            wchar_t cab[256];
            swprintf_s(cab, L"%-35s | %12s\r\n", traducoes[langIndex].colTeste, traducoes[langIndex].colPontuacao);
            logText += cab;
        }
        logText += L"-----------------------------------------------------------------------\r\n";
        SetWindowTextW(hEditLog, logText.c_str());
        SendMessageW(hEditLog, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
        SendMessageW(hEditLog, EM_SCROLLCARET, 0, 0);
        
        for (int i = 0; i < 100; ++i) {
            double scoreSingle = rodarSingleCore(testesFuncs[i], duracaoPorTeste, fatoresEscala[i]);
            meuUltimoScoreTestsSingle[i] = scoreSingle;
            meuUltimoTotalSingle += scoreSingle;
            
            wchar_t linha[256];
            swprintf_s(linha, L"%-35s | %12.1f\r\n", nomesTestesPT[i], scoreSingle);
            logText += linha;
            SetWindowTextW(hEditLog, logText.c_str());
            SendMessageW(hEditLog, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
            SendMessageW(hEditLog, EM_SCROLLCARET, 0, 0);
            
            wchar_t status[256];
            swprintf_s(status, L"%s %d/100", traducoes[langIndex].compSingleCore, i+1);
            SetWindowTextW(hStaticStatus, status);
        }
        
        benchmarkRealizado = true;
        
        std::wstring cpuCompleto = ObterNomeCompletoCPU();
        std::wstring nomeRegistroPC = cpuCompleto + L" (" + std::to_wstring(numThreads) + L" Threads)";
        bool novoRecorde = false;
        bool encontrado = false;
        
        for (size_t i = 1; i < pcsCadastrados.size(); ++i) {
            if (pcsCadastrados[i].nome == nomeRegistroPC) {
                encontrado = true;
                if (meuUltimoTotalMulti > pcsCadastrados[i].totalMultiCore) {
                    pcsCadastrados[i].totalMultiCore = meuUltimoTotalMulti;
                    pcsCadastrados[i].numThreads = numThreads;
                    for (int j = 0; j < 100; ++j)
                        pcsCadastrados[i].scoresMultiCore[j] = meuUltimoScoreTestsMulti[j];
                    novoRecorde = true;
                }
                if (meuUltimoTotalSingle > pcsCadastrados[i].totalSingleCore) {
                    pcsCadastrados[i].totalSingleCore = meuUltimoTotalSingle;
                    for (int j = 0; j < 100; ++j)
                        pcsCadastrados[i].scoresSingleCore[j] = meuUltimoScoreTestsSingle[j];
                    novoRecorde = true;
                }
                break;
            }
        }
        
        if (!encontrado) {
            PCReferencia novoPc;
            novoPc.nome = nomeRegistroPC;
            novoPc.numThreads = numThreads;
            novoPc.totalMultiCore = meuUltimoTotalMulti;
            novoPc.totalSingleCore = meuUltimoTotalSingle;
            for (int i = 0; i < 100; ++i) {
                novoPc.scoresMultiCore[i] = meuUltimoScoreTestsMulti[i];
                novoPc.scoresSingleCore[i] = meuUltimoScoreTestsSingle[i];
            }
            pcsCadastrados.push_back(novoPc);
            novoRecorde = true;
        }
        
        if (novoRecorde) SalvarListaNuvemNativo();
        
        AtualizarListaComparacao();
        ShowWindow(hStaticCompare, SW_SHOW);
        ShowWindow(hComboCompare, SW_SHOW);
        
        SetWindowTextW(hStaticStatus, traducoes[langIndex].statusPronto);
        
        // Reabilitar controles com verificação de validade da janela
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE);
            EnableWindow(hComboLang, TRUE);
            EnableWindow(hComboCompare, TRUE);
            EnableWindow(hComboFont, TRUE);
            
            // Reabilita o botão de fechar
            HMENU hMenu = GetSystemMenu(hwnd, FALSE);
            if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
        }
        
        AtualizarPainelComparativo();
    } catch (const std::exception& e) {
        // Em caso de erro, mostra mensagem e reabilita controles
        MessageBoxW(hwnd, traducoes[langIndex].msgErroBenchmark, traducoes[langIndex].tituloErro, MB_ICONERROR);
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE);
            EnableWindow(hComboLang, TRUE);
            EnableWindow(hComboCompare, TRUE);
            EnableWindow(hComboFont, TRUE);
             // Reabilita o botão de fechar
            HMENU hMenu = GetSystemMenu(hwnd, FALSE);
            if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
            SetWindowTextW(hStaticStatus, traducoes[langIndex].statusErroBenchmark);
        }
    } catch (...) {
        // Captura qualquer outra exceção
        MessageBoxW(hwnd, traducoes[langIndex].msgErroDesconhecido, traducoes[langIndex].tituloErro, MB_ICONERROR);
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE);
            EnableWindow(hComboLang, TRUE);
            EnableWindow(hComboCompare, TRUE);
            EnableWindow(hComboFont, TRUE);
             // Reabilita o botão de fechar
            HMENU hMenu = GetSystemMenu(hwnd, FALSE);
            if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
            SetWindowTextW(hStaticStatus, traducoes[langIndex].statusErroBenchmark);
        }
    }
    
    benchmarkEmAndamento = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hMainWnd = hwnd; // Salva handle global
            RECT workArea;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
            int screenW = workArea.right - workArea.left;
            int screenH = workArea.bottom - workArea.top;
            int winW = (1400 < screenW) ? 1400 : screenW;
            int winH = (700 < screenH) ? 700 : screenH;
            SetWindowPos(hwnd, NULL, 0, 0, winW, winH, SWP_NOZORDER);
            g_winW = winW;
            g_winH = winH;
            
            hStaticLang = CreateWindowW(L"STATIC", L"Idioma:", WS_VISIBLE | WS_CHILD, 15, 15, 60, 25, hwnd, (HMENU)ID_STATIC_LANG, NULL, NULL);
            hComboLang = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 80, 15, 150, 250, hwnd, (HMENU)ID_COMBO_LANG, NULL, NULL);
            
            hStaticFont = CreateWindowW(L"STATIC", L"Fonte:", WS_VISIBLE | WS_CHILD, 15, 15, 50, 25, hwnd, (HMENU)ID_STATIC_FONT, NULL, NULL);
            hComboFont = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 15, 15, 90, 250, hwnd, (HMENU)ID_COMBO_FONT, NULL, NULL);
            
            hStaticCompare = CreateWindowW(L"STATIC", L"Comparar:", WS_CHILD, 15, 15, 70, 25, hwnd, (HMENU)ID_STATIC_COMPARE, NULL, NULL);
            hComboCompare = CreateWindowW(L"COMBOBOX", L"", WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 15, 15, 280, 250, hwnd, (HMENU)ID_COMBO_PC_COMPARE, NULL, NULL);
            
            
            
            hBtnRun = CreateWindowW(L"BUTTON", L"Iniciar", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 15, 15, 90, 30, hwnd, (HMENU)ID_BTN_RUN, NULL, NULL);
            hStaticStatus = CreateWindowW(L"STATIC", L"Pronto para iniciar.", WS_VISIBLE | WS_CHILD, 15, 55, winW - 30, 25, hwnd, (HMENU)ID_STATIC_STATUS, NULL, NULL);
            
            hEditLog = CreateWindowW(L"RICHEDIT50W", L"",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY | WS_VSCROLL | WS_HSCROLL,
                                     15, 85, winW - 30, winH - 100, hwnd, (HMENU)ID_EDIT_LOG, NULL, NULL);
            SendMessageW(hEditLog, EM_EXLIMITTEXT, 0, (LPARAM)(1024 * 1024));
            SendMessageW(hEditLog, EM_SETBKGNDCOLOR, 0, RGB(255, 255, 255));
            
            // CORREÇÃO DA FONTE BRANCA: Definir formato inicial explícito
            CHARFORMAT2W cfInit = {0};
            cfInit.cbSize = sizeof(cfInit);
            cfInit.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR;
            cfInit.yHeight = 21 * 10;
            wcscpy_s(cfInit.szFaceName, L"Consolas");
            cfInit.crTextColor = RGB(0, 0, 0); // Preto
            SendMessageW(hEditLog, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cfInit);

            AtualizarFontesSimples(21);
            
            const wchar_t* linguagens[] = {
                L"Portugues (Brasil)", L"English (US)", L"Espanol", L"Frances",
                L"Alemao", L"Italiano", L"Chines", L"Russo",
                L"Coreano", L"Holandes", L"Polones", L"Japones"
            };
            for (int i = 0; i < 12; ++i) SendMessageW(hComboLang, CB_ADDSTRING, 0, (LPARAM)linguagens[i]);
            SendMessageW(hComboLang, CB_SETCURSEL, 0, 0);
            
            const wchar_t* fontSizes[] = { L"Pequena (18)", L"Media (21)", L"Grande (27)", L"Extra (33)" };
            for (int i = 0; i < 4; ++i) SendMessageW(hComboFont, CB_ADDSTRING, 0, (LPARAM)fontSizes[i]);
            SendMessageW(hComboFont, CB_SETCURSEL, 1, 0);
            
            AtualizarIdiomaInterface(0);
            PosicionarControlesTopo();
            CarregarListaNuvem(hwnd);
            break;
        }
        case WM_SYSCOMMAND:
            // Impede fechar a janela se o benchmark estiver rodando
            if ((wParam & 0xFFF0) == SC_CLOSE) {
                if (benchmarkEmAndamento) {
                    MessageBoxW(hwnd, traducoes[currentLangIndex].msgAguardeFechar, traducoes[currentLangIndex].tituloAguarde, MB_ICONWARNING);
                    return 0;
                }
            }
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, RGB(30, 30, 30));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_COMBO_LANG && HIWORD(wParam) == CBN_SELCHANGE) {
                int langIdx = (int)SendMessageW(hComboLang, CB_GETCURSEL, 0, 0);
                if (langIdx >= 0 && langIdx < 12) {
                    AtualizarIdiomaInterface(langIdx);
                }
            }
            else if (LOWORD(wParam) == ID_COMBO_FONT && HIWORD(wParam) == CBN_SELCHANGE) {
                int fontIdx = (int)SendMessageW(hComboFont, CB_GETCURSEL, 0, 0);
                int sizes[] = {18, 21, 27, 33};
                if (fontIdx >= 0 && fontIdx < 4) AtualizarFontesSimples(sizes[fontIdx]);
            }
            else if (LOWORD(wParam) == ID_COMBO_PC_COMPARE && HIWORD(wParam) == CBN_SELCHANGE) {
                if (benchmarkRealizado) AtualizarPainelComparativo();
            }
            else if (LOWORD(wParam) == ID_BTN_RUN && HIWORD(wParam) == BN_CLICKED) {
                int langIdx = (int)SendMessageW(hComboLang, CB_GETCURSEL, 0, 0);
                if (langIdx < 0 || langIdx >= 12) langIdx = 0;
                // Usa detach para rodar em background sem travar a UI, mas com tratamento de erro interno
                std::thread(ExecutarBenchmarkThread, hwnd, langIdx).detach();
            }
            break;
        case WM_DESTROY:
            if (hFontAtual) DeleteObject(hFontAtual);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    LoadLibraryW(L"Msftedit.dll");
    const wchar_t CLASS_NAME[] = L"BenchmarkAppClass";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassW(&wc);
    
    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Benchmark Multi-Core C++",
                                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                                CW_USEDEFAULT, CW_USEDEFAULT, 1400, 700, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) return 0;
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}