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
#define ID_COMBO_CPU_A 109
#define ID_COMBO_CPU_B 110
#define ID_STATIC_CPU_A 207
#define ID_STATIC_CPU_B 208

// IMPORTANTE: Substitua pelo ID real do seu documento npoint.io
const wchar_t* NPOINT_DOC_ID = L"XXXXXXXXXXXX"; 
std::wstring GetNpointUrl() { return L"https://api.npoint.io/" + std::wstring(NPOINT_DOC_ID); }
std::wstring GetNpointPath() { return L"/" + std::wstring(NPOINT_DOC_ID); }

struct IdiomaTextos {
    const wchar_t* tituloJanela;
    const wchar_t* labelLang;
    const wchar_t* labelCompare;
    const wchar_t* labelFont;
    const wchar_t* btnRun;
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
    const wchar_t* compMultiCore;
    const wchar_t* compSingleCore;
    const wchar_t* compTotal;
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
    const wchar_t* labelCpuA;
    const wchar_t* labelCpuB;
};

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

IdiomaTextos traducoes[] = {
    // 0: Portuguese
    { L"Benchmark Multi-Core C++", L"Idioma:", L"Comparar com:", L"Fonte:", L"Iniciar Benchmark",
      L"Pronto.", L"Executando MULTI-CORE...", L"Executando SINGLE-CORE...",
      L"RESULTADO FINAL (100 TESTES)", L"Nucleos: ", L"Teste", L"Seu PC", L"Outro PC", L"Dif", L"Pts",
      L"Selecione um PC...", L"Execute o benchmark primeiro.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTAL <<",
      L"*** SEU PC E MAIS RAPIDO (+", L"*** SEU PC E MAIS LENTO (", L"*** EMPATE TECNICO ***",
      L"*** SELECIONE UM PC PARA VER A COMPARACAO ***",
      L"Erro", L"Erro durante o benchmark.", L"Erro desconhecido.", L"Erro no benchmark.",
      L"Aguarde", L"Aguarde o termino antes de fechar.", L"CPU A:", L"CPU B:" },
    // 1: English
    { L"C++ Multi-Core Benchmark", L"Language:", L"Compare with:", L"Font:", L"Start Benchmark",
      L"Ready.", L"Running MULTI-CORE...", L"Running SINGLE-CORE...",
      L"FINAL SCORE (100 TESTS)", L"Cores: ", L"Test", L"Your PC", L"Other PC", L"Diff", L"Score",
      L"Select a PC...", L"Run benchmark first.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTAL <<",
      L"*** YOUR PC IS FASTER (+", L"*** YOUR PC IS SLOWER (", L"*** TECHNICAL TIE ***",
      L"*** SELECT A PC TO COMPARE ***",
      L"Error", L"Benchmark error.", L"Unknown error.", L"Benchmark error.",
      L"Wait", L"Wait for benchmark to finish.", L"CPU A:", L"CPU B:" },
    // 2: Spanish
    { L"Benchmark Multi-Core C++", L"Idioma:", L"Comparar con:", L"Fuente:", L"Iniciar",
      L"Listo.", L"Ejecutando MULTI-CORE...", L"Ejecutando SINGLE-CORE...",
      L"PUNTUACION FINAL", L"Nucleos: ", L"Prueba", L"Tu PC", L"Otro PC", L"Dif", L"Pts",
      L"Selecciona un PC...", L"Ejecuta el benchmark primero.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTAL <<",
      L"*** TU PC ES MAS RAPIDA (+", L"*** TU PC ES MAS LENTA (", L"*** EMPATE ***",
      L"*** SELECCIONA UN PC ***",
      L"Error", L"Error en benchmark.", L"Error desconocido.", L"Error.",
      L"Espera", L"Espera a que termine.", L"CPU A:", L"CPU B:" },
    // 3: French
    { L"Test C++ Multi-Core", L"Langue:", L"Comparer:", L"Police:", L"Demarrer",
      L"Pret.", L"Tests MULTI-CORE...", L"Tests SINGLE-CORE...",
      L"SCORE FINAL", L"Coeurs: ", L"Test", L"Votre PC", L"Autre PC", L"Diff", L"Score",
      L"Selectionnez un PC...", L"Lancez le benchmark.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTAL <<",
      L"*** VOTRE PC EST PLUS RAPIDE (+", L"*** VOTRE PC EST PLUS LENT (", L"*** EGALITE ***",
      L"*** SELECTIONNEZ UN PC ***",
      L"Erreur", L"Erreur benchmark.", L"Erreur inconnue.", L"Erreur.",
      L"Patientez", L"Attendez la fin du test.", L"CPU A :", L"CPU B :" },
    // 4: German
    { L"C++ Multi-Core Benchmark", L"Sprache:", L"Vergleichen:", L"Schrift:", L"Starten",
      L"Bereit.", L"MULTI-CORE Tests...", L"SINGLE-CORE Tests...",
      L"ERGEBNIS", L"Kerne: ", L"Test", L"Ihr PC", L"Anderer PC", L"Diff", L"Pkt",
      L"PC waehlen...", L"Bitte zuerst starten.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> GESAMT <<",
      L"*** IHR PC IST SCHNELLER (+", L"*** IHR PC IST LANGSAMER (", L"*** UNENTSCHIEDEN ***",
      L"*** PC AUSWAEHLEN ***",
      L"Fehler", L"Benchmark-Fehler.", L"Unbekannter Fehler.", L"Fehler.",
      L"Warten", L"Warten bis fertig.", L"CPU A:", L"CPU B:" },
    // 5: Italian
    { L"Benchmark C++ Multi-Core", L"Lingua:", L"Confronta:", L"Font:", L"Avvia",
      L"Pronto.", L"Test MULTI-CORE...", L"Test SINGLE-CORE...",
      L"PUNTEGGIO FINALE", L"Core: ", L"Test", L"Tuo PC", L"Altro PC", L"Diff", L"Pts",
      L"Seleziona un PC...", L"Esegui prima il test.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTALE <<",
      L"*** IL TUO PC E PIU VELOCE (+", L"*** IL TUO PC E PIU LENTO (", L"*** PAREGGIO ***",
      L"*** SELEZIONA UN PC ***",
      L"Errore", L"Errore benchmark.", L"Errore sconosciuto.", L"Errore.",
      L"Attendi", L"Attendi la fine.", L"CPU A:", L"CPU B:" },
    // 6: Chinese
    { L"C++ Multi-Core Benchmark", L"Yan Yu:", L"Bi Jiao:", L"Zi Ti:", L"Kai Shi",
      L"Jiu Xu", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"ZUI ZHONG DE FEN", L"He Xin: ", L"Ce Shi", L"Ni De PC", L"Qi Ta PC", L"Cha Yi", L"Fen",
      L"Xuan Ze PC...", L"Qing Xian Yun Xing.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> ZONG JI <<",
      L"*** NI DE PC GENG KUAI (+", L"*** NI DE PC GENG MAN (", L"*** PING JU ***",
      L"*** XUAN ZE PC ***",
      L"Cuo Wu", L"Benchmark Cuo Wu.", L"Wei Zhi Cuo Wu.", L"Cuo Wu.",
      L"Deng Dai", L"Deng Dai Wan Cheng.", L"CPU A:", L"CPU B:" },
    // 7: Russian
    { L"C++ Multi-Core Benchmark", L"Yazyk:", L"Sravnit:", L"Shrift:", L"Start",
      L"Gotov.", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"ITOG", L"Yadra: ", L"Test", L"Vash PK", L"Drugoy PK", L"Razn", L"Pts",
      L"Vyberite PK...", L"Snachala zapustite.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> ITOGO <<",
      L"*** VASH PK BYSTREE (+", L"*** VASH PK MEDLENNEE (", L"*** NICHYA ***",
      L"*** VYBERITE PK ***",
      L"Oshibka", L"Oshibka testa.", L"Neizvestnaya oshibka.", L"Oshibka.",
      L"Zhdite", L"Zhdite okonchaniya.", L"CPU A:", L"CPU B:" },
    // 8: Korean
    { L"C++ Multi-Core Benchmark", L"Eon Eo:", L"Bi Gyo:", L"Geul Ggol:", L"Si Jak",
      L"Jun Bi", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"CHOE JONG JEOM SU", L"Ko Eo: ", L"Te Seuteu", L"Nae PC", L"Da Reun PC", L"Cha I", L"Jeom",
      L"PC Seon Taek...", L"Meon Jeo Sil Haeng.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> HAB GYE <<",
      L"*** NAE PC GA DEO PPA REUM (+", L"*** NAE PC GA DEO NEU RIM (", L"*** MU SEUNG BU ***",
      L"*** PC SEON TAEK ***",
      L"O Ryu", L"Benchmark O Ryu.", L"Al Su Eom Neun O Ryu.", L"O Ryu.",
      L"Gi Da Rim", L"Gi Da Ryeo Ju Se Yo.", L"CPU A:", L"CPU B:" },
    // 9: Dutch
    { L"C++ Multi-Core Benchmark", L"Taal:", L"Vergelijk:", L"Lettertype:", L"Start",
      L"Klaar.", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"RESULTAAT", L"Kernen: ", L"Test", L"Jouw PC", L"Andere PC", L"Verschil", L"Score",
      L"Selecteer PC...", L"Voer eerst uit.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> TOTAAL <<",
      L"*** JOUW PC IS SNELLER (+", L"*** JOUW PC IS LANGZAMER (", L"*** GELIJKSPEL ***",
      L"*** SELECTEER PC ***",
      L"Fout", L"Benchmark fout.", L"Onbekende fout.", L"Fout.",
      L"Wacht", L"Wacht tot voltooid.", L"CPU A:", L"CPU B:" },
    // 10: Polish
    { L"Benchmark C++ Multi-Core", L"Jezyk:", L"Porownaj:", L"Czcionka:", L"Start",
      L"Gotowy.", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"WYNIK", L"Rdzenie: ", L"Test", L"Twoj PC", L"Inny PC", L"Roznica", L"Wynik",
      L"Wybierz PC...", L"Najpierw uruchom.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> RAZEM <<",
      L"*** TWOJ PC SZYBSZY (+", L"*** TWOJ PC WOLNIEJSZY (", L"*** REMIS ***",
      L"*** WYBIERZ PC ***",
      L"Blad", L"Blad testu.", L"Nieznany blad.", L"Blad.",
      L"Czekaj", L"Czekaj na koniec.", L"CPU A:", L"CPU B:" },
    // 11: Japanese
    { L"C++ Multi-Core Benchmark", L"Nihongo:", L"Hikaku:", L"Font:", L"Kaishi",
      L"Junbi", L"MULTI-CORE...", L"SINGLE-CORE...",
      L"SAISHUU SUKOA", L"Koa: ", L"Tesuto", L"Anata PC", L"Hoka PC", L"Sai", L"Sukoa",
      L"PC Sentaku...", L"Saisho Ni Jikkou.",
      L"[MULTI-CORE]", L"[SINGLE-CORE]", L">> GOUKEI <<",
      L"*** ANATA PC HAYAI (+", L"*** ANATA PC OSOI (", L"*** HIKIWAKE ***",
      L"*** PC SENTAKU ***",
      L"Era", L"Benchmark Era.", L"Fumei Era.", L"Era.",
      L"Machi", L"Shuuryou Wo Machi.", L"CPU A:", L"CPU B:" }
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
HWND hMainWnd = NULL;
HWND hStaticCpuA = NULL;
HWND hComboCpuA = NULL;
HWND hStaticCpuB = NULL;
HWND hComboCpuB = NULL;

HFONT hFontAtual = NULL;
int currentFontSize = 21;
int currentLangIndex = 0;
int g_winW = 1400;
int g_winH = 700;

std::wstring g_cabecalhoAtual = L"";
bool g_modoCpuXCpuAtivo = false;

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
bool benchmarkEmAndamento = false;

void AtualizarFontesSimples(int fontSize);
void AtualizarIdiomaInterface(int langIndex);
void AtualizarPainelComparativo();
void AtualizarListaComparacao();
void PosicionarControlesTopo();
void AtualizarPainelPrincipal();

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

std::wstring TruncarTexto(const std::wstring& texto, size_t maxLen) {
    if (texto.size() <= maxLen) return texto;
    return texto.substr(0, maxLen - 1) + L".";
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
    if (lastChar != std::wstring::npos) nome.erase(lastChar + 1);
    return nome;
}

// =============================================================================
// FUNÇÕES DE REDE BLINDADAS (PROVA DE FALHAS)
// =============================================================================

std::string GerarJsonCompleto() {
    std::string json = "{\"data\":[";
    bool primeiro = true;
    for (size_t i = 1; i < pcsCadastrados.size(); ++i) {
        if (!primeiro) json += ",";
        primeiro = false;
        
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

std::string BaixarJsonNuvem() {
    std::string resposta;
    HINTERNET hInternet = InternetOpenW(L"BenchmarkAppClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "";
    
    std::wstring url = GetNpointUrl();
    DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE;
    HINTERNET hFile = InternetOpenUrlW(hInternet, url.c_str(), NULL, 0, flags, 0);
    
    if (hFile) {
        char buffer[8192];
        DWORD bytesLidos = 0;
        while (InternetReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesLidos) && bytesLidos > 0) {
            buffer[bytesLidos] = '\0';
            resposta += buffer;
        }
        InternetCloseHandle(hFile);
    }
    InternetCloseHandle(hInternet);
    return resposta;
}

std::vector<double> ExtrairArrayDouble(const std::string& json, size_t startPos) {
    std::vector<double> result;
    size_t pos = json.find('[', startPos);
    if (pos == std::string::npos) return result;
    pos++;
    while (pos < json.size()) {
        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) pos++;
        if (pos >= json.size() || json[pos] == ']') break;
        size_t numStart = pos;
        while (pos < json.size() && json[pos] != ',' && json[pos] != ']') pos++;
        if (pos > numStart) {
            try { result.push_back(std::stod(json.substr(numStart, pos - numStart))); } catch (...) {}
        }
        if (pos < json.size() && json[pos] == ',') pos++;
    }
    return result;
}

void MesclarDadosNaMemoria(const std::string& jsonNuvem) {
    size_t posArray = jsonNuvem.find("\"data\":[");
    if (posArray == std::string::npos) return; 

    size_t pos = posArray + 7;
    while ((pos = jsonNuvem.find("{\"nome\"", pos)) != std::string::npos) {
        size_t endObj = jsonNuvem.find("}", pos);
        if (endObj == std::string::npos) break;
        
        size_t startNome = jsonNuvem.find(":\"", pos) + 2;
        size_t endNome = jsonNuvem.find("\"", startNome);
        if (startNome == std::string::npos || endNome == std::string::npos || endNome > endObj) { pos++; continue; }
        
        std::string nomeUtf8 = jsonNuvem.substr(startNome, endNome - startNome);
        std::wstring wNome = Utf8ToWstring(nomeUtf8);
        
        double totalMulti = 0, totalSingle = 0;
        int threads = 0;
        
        size_t posTotalMulti = jsonNuvem.find("\"totalMulti\":", endNome);
        if (posTotalMulti != std::string::npos && posTotalMulti < endObj) 
            try { totalMulti = std::stod(jsonNuvem.substr(posTotalMulti + 13)); } catch(...) {}
            
        size_t posTotalSingle = jsonNuvem.find("\"totalSingle\":", endNome);
        if (posTotalSingle != std::string::npos && posTotalSingle < endObj) 
            try { totalSingle = std::stod(jsonNuvem.substr(posTotalSingle + 14)); } catch(...) {}
            
        size_t posThreads = jsonNuvem.find("\"threads\":", endNome);
        if (posThreads != std::string::npos && posThreads < endObj) 
            try { threads = std::stoi(jsonNuvem.substr(posThreads + 10)); } catch(...) {}

        std::vector<double> scoresMultiVec = ExtrairArrayDouble(jsonNuvem, endNome);
        size_t posEndFirstArray = jsonNuvem.find(']', endNome);
        std::vector<double> scoresSingleVec;
        if (posEndFirstArray != std::string::npos && posEndFirstArray < endObj) 
            scoresSingleVec = ExtrairArrayDouble(jsonNuvem, posEndFirstArray);
        
        bool existe = false;
        for (size_t k = 1; k < pcsCadastrados.size(); ++k) {
            if (pcsCadastrados[k].nome == wNome) {
                existe = true;
                bool atualizou = false;
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
                if (atualizou && threads > 0) pcsCadastrados[k].numThreads = threads;
                break;
            }
        }
        
        if (!existe) {
            PCReferencia novo;
            novo.nome = wNome;
            novo.totalMultiCore = totalMulti;
            novo.totalSingleCore = totalSingle;
            novo.numThreads = threads;
            for(int s=0; s<100; ++s) {
                novo.scoresMultiCore[s] = (s < (int)scoresMultiVec.size()) ? scoresMultiVec[s] : 0.0;
                novo.scoresSingleCore[s] = (s < (int)scoresSingleVec.size()) ? scoresSingleVec[s] : 0.0;
            }
            pcsCadastrados.push_back(novo);
        }
        pos = endObj + 1;
    }
}

void CarregarListaNuvem(HWND hwnd) {
    std::string jsonNuvem = BaixarJsonNuvem();
    if (!jsonNuvem.empty() && jsonNuvem.find("\"data\"") != std::string::npos) {
        MesclarDadosNaMemoria(jsonNuvem);
    }
}

bool SalvarListaNuvemNativo() {
    // PASSO CRÍTICO: Baixa o estado atual ANTES de salvar
    std::string jsonAtualNuvem = BaixarJsonNuvem();
    
    // Se não conseguir baixar ou JSON inválido, ABORTA para não apagar dados
    if (jsonAtualNuvem.empty() || jsonAtualNuvem.find("\"data\"") == std::string::npos) {
        return false; 
    }
    
    // Sincroniza memória local com nuvem (garante que temos tudo)
    MesclarDadosNaMemoria(jsonAtualNuvem);
    
    // Gera o JSON completo baseado na memória sincronizada
    std::string jsonData = GerarJsonCompleto();
    
    // Validação final: Nunca enviar JSON vazio
    if (jsonData == "{\"data\":[]}" || jsonData.length() < 20) {
        return false;
    }
    
    HINTERNET hSession = InternetOpenW(L"BenchmarkClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hSession) return false;
    HINTERNET hConnect = InternetConnectW(hSession, L"api.npoint.io", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) { InternetCloseHandle(hSession); return false; }
    
    std::wstring path = GetNpointPath();
    HINTERNET hRequest = HttpOpenRequestW(hConnect, L"POST", path.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
    if (!hRequest) { InternetCloseHandle(hConnect); InternetCloseHandle(hSession); return false; }
    
    std::wstring headers = L"Content-Type: application/json\r\nAccept: */*\r\n";
    BOOL enviado = HttpSendRequestW(hRequest, headers.c_str(), (DWORD)headers.size(), (LPVOID)jsonData.c_str(), (DWORD)jsonData.size());
    
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    
    return enviado == TRUE;
}

// =============================================================================
// 100 FUNÇÕES DE BENCHMARK (MANTIDAS IGUAIS)
// =============================================================================
double calcularScoreNormalizado(long long totalOps, double tempoSegundos, double fatorEscala) {
    if (tempoSegundos <= 0) return 0;
    return ((double)totalOps / tempoSegundos / fatorEscala) / 100.0;
}

long long benchmarkPontoFlutuante(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double r=0;while(true){for(int i=1;i<=1000;++i)r+=std::sin(i)*std::cos(i)+std::sqrt(i);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMatrizInteiros(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int n=128;std::vector<int> a(n*n,3),b(n*n,5),r(n*n,0);while(true){for(int i=0;i<n;++i)for(int j=0;j<n;++j){int s=0;for(int k=0;k<n;++k)s+=a[i*n+k]*b[k*n+j];r[i*n+j]=s;}c+=n*n;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkOrdenacao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1337);std::vector<int> v(10000);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100000;});std::sort(v.begin(),v.end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPrimos(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0,n=500000;while(true){bool p=true;for(long long i=2;i<=std::sqrt(n);++i)if(n%i==0){p=false;break;}c++;n++;if(n>900000)n=500000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAlocacaoMemoria(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){{std::vector<double> b(2048,3.14);volatile double v=b[1024];(void)v;}c+=2048;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBitwise(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;unsigned int v=0x12345678;while(true){for(int i=0;i<1000;++i){v^=(v<<13);v^=(v>>17);v^=(v<<5);}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHashSimulado(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;unsigned long long h=5381;char txt[]="BenchmarkMassivoMultiThread";while(true){for(int i=0;i<sizeof(txt)-1;++i)h=((h<<5)+h)+txt[i];c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCacheStress(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int n=65536;std::vector<int> b(n,1);while(true){for(int i=0;i<n;i+=7)b[(i*31)%n]+=i;c+=n;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPolinomios(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double x=1.0001;while(true){for(int i=0;i<500;++i){x=x*x+2.0*x+1.0;if(x>1e10)x=1.0001;}c+=500;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLogicaArray(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<bool> f(2048,false);while(true){for(size_t i=0;i<f.size();++i){f[i]=!f[i];if(i>0)f[i]=f[i]^f[i-1];}c+=f.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCriptografia(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;uint32_t h0=0x6a09e667,h1=0xbb67ae85,h2=0x3c6ef372,h3=0xa54ff53a;while(true){for(int i=0;i<100;++i){uint32_t s0=(h0>>2|h0<<30)^(h0>>13|h0<<19)^(h0>>22|h0<<10);uint32_t s1=(h1>>6|h1<<26)^(h1>>11|h1<<21)^(h1>>25|h1<<7);h3=h2;h2=h1;h1=h0;h0=s0+s1+h3+i;}c+=100;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCompressao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<char> data(1024,'A');while(true){int cnt=1;for(size_t i=1;i<data.size();++i){if(data[i]==data[i-1])cnt++;else cnt=1;}c+=data.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFisica(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct Body{double x,y,vx,vy;};std::vector<Body> bodies(50);for(auto&b:bodies){b.x=rand()%100;b.y=rand()%100;b.vx=1;b.vy=1;}while(true){for(auto&b:bodies){b.x+=b.vx;b.y+=b.vy;if(b.x>100||b.x<0)b.vx*=-1;if(b.y>100||b.y<0)b.vy*=-1;}c+=bodies.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkGameOfLife(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int w=100,h=100;std::vector<std::vector<bool>> g(w,std::vector<bool>(h,false)),n(w,std::vector<bool>(h,false));std::mt19937 rng(42);for(int x=0;x<w;++x)for(int y=0;y<h;++y)g[x][y]=(rng()%2==0);while(true){for(int x=1;x<w-1;++x)for(int y=1;y<h-1;++y){int nb=0;for(int dx=-1;dx<=1;++dx)for(int dy=-1;dy<=1;++dy){if(dx==0&&dy==0)continue;if(g[x+dx][y+dy])nb++;}if(g[x][y])n[x][y]=(nb==2||nb==3);else n[x][y]=(nb==3);}std::swap(g,n);c+=w*h;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAudio(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double p=0;while(true){for(int i=0;i<4410;++i){p+=440.0/44100.0;if(p>1.0)p-=1.0;volatile double s=std::sin(p*2.0*3.14159);}c+=4410;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRede(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> pkt(1500,0xFF);while(true){uint32_t cs=0;for(size_t i=0;i<pkt.size();i+=2)cs+=(pkt[i]<<8)|pkt[i+1];c+=pkt.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkIA(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;double w[10]={0.5},in[10]={1.0};while(true){double s=0;for(int i=0;i<10;++i)s+=w[i]*in[i];double o=1.0/(1.0+std::exp(-s));for(int i=0;i<10;++i)w[i]+=0.001*o;c+=10;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDatabase(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> idx(10000);std::iota(idx.begin(),idx.end(),0);while(true){int tgt=rand()%10000;bool f=std::binary_search(idx.begin(),idx.end(),tgt);c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkParticulas(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct P{float x,y,l;};std::vector<P> ps(1000);while(true){for(auto&p:ps){p.x+=0.1;p.y+=0.1;p.l-=0.01;if(p.l<=0){p.l=1.0;p.x=0;p.y=0;}}c+=ps.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSteganografia(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> img(4096,128),sec(512,1);while(true){for(size_t i=0;i<sec.size();++i)img[i]=(img[i]&0xFE)|(sec[i]&1);c+=sec.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMandelbrot(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int y=-100;y<=100;++y)for(int x=-100;x<=100;++x){double zx=0,zy=0,cx=x/50.0,cy=y/50.0;int i=0;for(;i<100&&(zx*zx+zy*zy)<4.0;++i){double tmp=zx*zx-zy*zy+cx;zy=2.0*zx*zy+cy;zx=tmp;}c+=i;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFourier(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> sig(1024,0);std::mt19937 rng(99);for(auto&s:sig)s=(rng()%1000)/1000.0;while(true){for(int k=0;k<1024;++k){double re=0,im=0;for(int n=0;n<1024;++n){double a=2.0*3.14159*k*n/1024;re+=sig[n]*std::cos(a);im-=sig[n]*std::sin(a);}}c+=1024*1024;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkShortestPath(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>> g(V,std::vector<int>(V,999));std::mt19937 rng(77);for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(i!=j)g[i][j]=rng()%100;while(true){std::vector<int> dist(V,999999);std::vector<bool> vis(V,false);dist[0]=0;for(int cnt=0;cnt<V-1;++cnt){int u=-1;for(int v=0;v<V;++v)if(!vis[v]&&(u==-1||dist[v]<dist[u]))u=v;if(dist[u]==999999)break;vis[u]=true;for(int v=0;v<V;++v)if(!vis[v]&&g[u][v]!=999&&dist[u]+g[u][v]<dist[v])dist[v]=dist[u]+g[u][v];}c+=V*V;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRegex(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string txt="abc123def456ghi789jkl012mno345pqr678stu901vwx234yz";while(true){for(int i=0;i<10000;++i){bool m=false;for(size_t j=0;j<=txt.size()-3;++j)if(std::isdigit(txt[j])&&std::isdigit(txt[j+1])&&std::isdigit(txt[j+2])){m=true;break;}if(m)c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkXML(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string xml="<root><item id='1'><name>Test</name></item></root>";while(true){size_t p=0;while((p=xml.find('<',p))!=std::string::npos){size_t e=xml.find('>',p);if(e==std::string::npos)break;p=e+1;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMultiplicacaoMatriz(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=200;std::vector<std::vector<double>> A(N,std::vector<double>(N,1.5)),B(N,std::vector<double>(N,2.0)),C(N,std::vector<double>(N,0));while(true){for(int i=0;i<N;++i)for(int j=0;j<N;++j)for(int k=0;k<N;++k)C[i][j]+=A[i][k]*B[k][j];c+=N*N*N;for(int i=0;i<N;++i)for(int j=0;j<N;++j)C[i][j]=0;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRayTracing(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct S{double x,y,z,r;};std::vector<S> sp={{0,0,5,1},{2,1,6,1.5},{-2,-1,7,1.2}};while(true){for(int py=0;py<100;++py)for(int px=0;px<100;++px){double rx=(px-50)/50.0,ry=(py-50)/50.0,rz=1.0;for(auto&s:sp){double a=rx*rx+ry*ry+rz*rz;double b=2*(rx*(-s.x)+ry*(-s.y)+rz*(-s.z));double cc=s.x*s.x+s.y*s.y+s.z*s.z-s.r*s.r;if(b*b-4*a*cc>=0)c++;}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkGenetico(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int PS=100,G=50;std::mt19937 rng(12345);std::vector<std::vector<int>> pop(PS,std::vector<int>(G));for(auto&i:pop)for(auto&g:i)g=rng()%2;while(true){for(auto&i:pop){int f=0;for(int g:i)f+=g;c++;}for(int i=0;i<PS/2;++i){int cp=rng()%G;for(int j=cp;j<G;++j)std::swap(pop[i][j],pop[PS-1-i][j]);}for(auto&i:pop)if(rng()%100<5){int p=rng()%G;i[p]=!i[p];}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFluidos(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int G=64;std::vector<std::vector<double>> den(G,std::vector<double>(G,1.0)),nd(G,std::vector<double>(G,0));while(true){for(int i=1;i<G-1;++i)for(int j=1;j<G-1;++j)nd[i][j]=(den[i][j]+den[i-1][j]+den[i+1][j]+den[i][j-1]+den[i][j+1])/5.0;std::swap(den,nd);c+=G*G;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAESSimulado(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> blk(16,0xAA),key(16,0xBB);while(true){for(int r=0;r<10;++r){for(int i=0;i<16;++i)blk[i]=(blk[i]<<3)^(blk[i]>>5)^key[i];std::rotate(blk.begin(),blk.begin()+(r%4),blk.end());for(int i=0;i<12;++i)blk[i]^=blk[i+1]^blk[i+2];for(int i=0;i<16;++i)blk[i]^=key[i];}c+=16;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAStar(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int G=50;std::mt19937 rng(54321);while(true){std::vector<std::vector<bool>> w(G,std::vector<bool>(G,true));for(int i=0;i<G*G/4;++i)w[rng()%G][rng()%G]=false;std::vector<std::vector<int>> dist(G,std::vector<int>(G,-1));std::queue<std::pair<int,int>> q;dist[0][0]=0;q.push({0,0});int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};while(!q.empty()){auto cur=q.front();q.pop();int x=cur.first,y=cur.second;c++;for(auto&d:dirs){int nx=x+d[0],ny=y+d[1];if(nx>=0&&nx<G&&ny>=0&&ny<G&&w[nx][ny]&&dist[nx][ny]==-1){dist[nx][ny]=dist[x][y]+1;q.push({nx,ny});}}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMonteCarlo(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0,in=0;std::mt19937 rng(98765);std::uniform_real_distribution<double> dist(0,1);while(true){for(int i=0;i<10000;++i){double x=dist(rng),y=dist(rng);if(x*x+y*y<=1)in++;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkConvolucao(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int W=128,H=128,K=3;std::vector<std::vector<double>> img(H,std::vector<double>(W,0.5)),res(H,std::vector<double>(W,0));std::vector<std::vector<double>> krn={{1,2,1},{2,4,2},{1,2,1}};while(true){for(int y=1;y<H-1;++y)for(int x=1;x<W-1;++x){double s=0;for(int ky=0;ky<K;++ky)for(int kx=0;kx<K;++kx)s+=img[y+ky-1][x+kx-1]*krn[ky][kx];res[y][x]=s/16.0;}c+=(H-2)*(W-2)*K*K;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBTree(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::map<int,int> bt;std::mt19937 rng(11111);while(true){for(int i=0;i<1000;++i){bt[rng()%100000]=rng();c++;}for(int i=0;i<500;++i){auto it=bt.find(rng()%100000);if(it!=bt.end())c++;}for(int i=0;i<100;++i){auto it=bt.find(rng()%100000);if(it!=bt.end()){bt.erase(it);c++;}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkTensor(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int D=20;std::vector<std::vector<std::vector<double>>> a(D,std::vector<std::vector<double>>(D,std::vector<double>(D,1))),b(D,std::vector<std::vector<double>>(D,std::vector<double>(D,2))),r(D,std::vector<std::vector<double>>(D,std::vector<double>(D,0)));while(true){for(int i=0;i<D;++i)for(int j=0;j<D;++j)for(int k=0;k<D;++k)r[i][j][k]=a[i][j][k]*b[i][j][k];c+=D*D*D;for(int i=0;i<D;++i)for(int j=0;j<D;++j)for(int k=0;k<D;++k)r[i][j][k]=0;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFatorial(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long r=1;for(int i=1;i<=20;++i)r*=i;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*20;}
long long benchmarkFibonacci(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long a=0,b=1;for(int i=0;i<100;++i){long long tmp=a+b;a=b;b=tmp;}c+=100;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHanoi(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;auto h=[&](auto self,int n,int f,int to,int a)->void{if(n==1){c++;return;}self(self,n-1,f,a,to);c++;self(self,n-1,a,to,f);};while(true){h(h,15,1,3,2);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCrivo(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=100000;std::vector<bool> ip(N,true);while(true){std::fill(ip.begin(),ip.end(),true);ip[0]=ip[1]=false;for(int i=2;i*i<N;++i)if(ip[i])for(int j=i*i;j<N;j+=i)ip[j]=false;c+=N;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMDC(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){for(int i=0;i<10000;++i){long long a=rng()%1000000,b=rng()%1000000;while(b){long long tmp=b;b=a%b;a=tmp;}c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPotenciaMod(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){long long b=2,e=100000,m=1000000007,r=1;b%=m;while(e>0){if(e%2==1)r=(r*b)%m;e>>=1;b=(b*b)%m;}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkRaizNewton(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double x=2;for(int i=0;i<1000;++i)x=0.5*(x+10.0/x);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSenoTaylor(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double x=1,term=x,sum=x;for(int n=1;n<20;++n){term*=-x*x/((2*n)*(2*n+1));sum+=term;}c+=20;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkExpMath(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double r=std::exp(1.0);(void)r;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*1000;}
long long benchmarkLogNat(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){double r=std::log(2.71828);(void)r;c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*1000;}
long long benchmarkAbsBulk(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> v(10000,-5.5);while(true){for(auto&x:v)x=std::abs(x);c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRoundBulk(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> v(10000,3.14159);while(true){for(auto&x:v)x=std::round(x);c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkClamp(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){for(int i=0;i<10000;++i){double v=rng()%1000;double cl=std::max(0.0,std::min(100.0,v));(void)cl;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLerp(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int i=0;i<10000;++i){double tt=(double)i/10000.0;double r=0.0+tt*(100.0-0.0);(void)r;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSpline(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(double tt=0;tt<1.0;tt+=0.01){double r=2*tt*tt*tt-3*tt*tt+1;(void)r;c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBubbleSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(500);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=0;i<v.size();++i)for(size_t j=0;j<v.size()-1;++j)if(v[j]>v[j+1])std::swap(v[j],v[j+1]);c+=v.size()*v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkInsertionSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(1000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=1;i<v.size();++i){int k=v[i];int j=i-1;while(j>=0&&v[j]>k){v[j+1]=v[j];j--;}v[j+1]=k;}c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkSelectionSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(800);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});for(size_t i=0;i<v.size();++i){size_t mi=i;for(size_t j=i+1;j<v.size();++j)if(v[j]<v[mi])mi=j;std::swap(v[i],v[mi]);}c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkQuickSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(2000);std::mt19937 rng(1);auto qs=[&](auto self,int l,int r,std::vector<int>& a)->void{if(l<r){int p=a[l+(r-l)/2];int i=l,j=r;while(i<=j){while(a[i]<p)i++;while(a[j]>p)j--;if(i<=j){std::swap(a[i],a[j]);i++;j--;c++;}}self(self,l,j,a);self(self,i,r,a);}};while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});qs(qs,0,v.size()-1,v);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMergeSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(2000);std::mt19937 rng(1);auto ms=[&](auto self,std::vector<int>& a)->void{if(a.size()<=1)return;int m=a.size()/2;std::vector<int> l(a.begin(),a.begin()+m),r(a.begin()+m,a.end());self(self,l);self(self,r);size_t i=0,j=0,k=0;while(i<l.size()&&j<r.size()){if(l[i]<=r[j])a[k++]=l[i++];else a[k++]=r[j++];c++;}while(i<l.size())a[k++]=l[i++];while(j<r.size())a[k++]=r[j++];};while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});ms(ms,v);if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHeapSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});std::make_heap(v.begin(),v.end());std::sort_heap(v.begin(),v.end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCountingSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(5000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100;});std::vector<int> cnt(100,0);for(int x:v)cnt[x]++;c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRadixSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%100000;});int mx=*std::max_element(v.begin(),v.end());for(int exp=1;mx/exp>0;exp*=10){std::vector<int> out(v.size()),cnt(10,0);for(int i=0;i<v.size();i++)cnt[(v[i]/exp)%10]++;for(int i=1;i<10;i++)cnt[i]+=cnt[i-1];for(int i=v.size()-1;i>=0;i--){out[cnt[(v[i]/exp)%10]-1]=v[i];cnt[(v[i]/exp)%10]--;}for(int i=0;i<v.size();i++)v[i]=out[i];c+=v.size();}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBucketSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return(double)(rng()%1000)/1000.0;});int n=v.size();std::vector<std::vector<double>> bk(n);for(int i=0;i<n;i++){int bi=n*v[i];bk[bi].push_back(v[i]);}for(int i=0;i<n;i++)std::sort(bk[i].begin(),bk[i].end());c+=v.size();if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkShellSort(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(2000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng()%1000;});int n=v.size();for(int gap=n/2;gap>0;gap/=2)for(int i=gap;i<n;i++){int tmp=v[i];int j;for(j=i;j>=gap&&v[j-gap]>tmp;j-=gap){v[j]=v[j-gap];c++;}v[j]=tmp;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
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
long long benchmarkHexDump(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> data(1000,0xFF);while(true){std::stringstream ss;for(uint8_t b:data)ss<<std::hex<<std::setw(2)<<std::setfill('0')<<(int)b;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCRC32(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> data(1000,1);while(true){uint32_t crc=0xFFFFFFFF;for(uint8_t b:data){crc^=b;for(int i=0;i<8;i++)crc=(crc>>1)^(0xEDB88320&(-(crc&1)));}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkAdler32(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> data(1000,1);while(true){uint32_t a=1,b=0;for(uint8_t d:data){a=(a+d)%65521;b=(b+a)%65521;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFletcher(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> data(1000,1);while(true){uint16_t s1=0,s2=0;for(uint8_t d:data){s1=(s1+d)%255;s2=(s2+s1)%255;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkXORCipher(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<uint8_t> data(1000,1);uint8_t key=0xAA;while(true){for(auto&d:data)d^=key;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkROT13(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A');while(true){for(auto&ch:s)if(ch>='A'&&ch<='Z')ch='A'+(ch-'A'+13)%26;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkCaesar(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A');int shift=3;while(true){for(auto&ch:s)if(ch>='A'&&ch<='Z')ch='A'+(ch-'A'+shift)%26;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVigenere(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s(1000,'A'),key="KEY";while(true){for(size_t i=0;i<s.size();++i){char k=key[i%key.size()];if(s[i]>='A'&&s[i]<='Z')s[i]='A'+(s[i]-'A'+k-'A')%26;}c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkRandomFill(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(10000);std::mt19937 rng(1);while(true){std::generate(v.begin(),v.end(),[&rng](){return rng();});c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMemSet(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(10000);while(true){memset(v.data(),0,v.size()*sizeof(int));c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMemMove(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<int> v(10000,1),dst(10000);while(true){memcpy(dst.data(),v.data(),v.size()*sizeof(int));c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecAdd(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> a(10000,1),b(10000,2),r(10000);while(true){for(size_t i=0;i<a.size();++i)r[i]=a[i]+b[i];c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecDot(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::vector<double> a(10000,1),b(10000,2);while(true){double r=0;for(size_t i=0;i<a.size();++i)r+=a[i]*b[i];c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkVecCross(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;while(true){for(int i=0;i<10000;++i){double ax=1,ay=2,az=3,bx=4,by=5,bz=6;double cx=ay*bz-az*by,cy=az*bx-ax*bz,cz=ax*by-ay*bx;(void)cx;(void)cy;(void)cz;}c+=10000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkMatDet(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=10;std::vector<std::vector<double>> m(N,std::vector<double>(N,1.5));while(true){double det=1;for(int i=0;i<N;++i){for(int j=i+1;j<N;++j){double f=m[j][i]/m[i][i];for(int k=i;k<N;++k)m[j][k]-=f*m[i][k];}det*=m[i][i];}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkMatInv(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=5;std::vector<std::vector<double>> m(N,std::vector<double>(N,0));for(int i=0;i<N;++i)m[i][i]=1;while(true){double det=1;for(int i=0;i<N;++i){for(int j=i+1;j<N;++j){double f=m[j][i]/m[i][i];for(int k=i;k<N;++k)m[j][k]-=f*m[i][k];}det*=m[i][i];}c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c*100;}
long long benchmarkLLTraverse(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;struct Node{int val;Node*next;};Node*head=nullptr;for(int i=0;i<1000;++i){Node*n=new Node{i,head};head=n;}while(true){Node*cur=head;while(cur){c++;cur=cur->next;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBST(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::set<int> bst;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)bst.insert(rng()%100000);c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkHashMap(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::unordered_map<int,int> hm;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)hm[rng()%100000]=i;c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPriorityQ(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::priority_queue<int> pq;std::mt19937 rng(1);while(true){for(int i=0;i<1000;++i)pq.push(rng()%100000);for(int i=0;i<1000;++i)if(!pq.empty())pq.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkStack(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::stack<int> st;while(true){for(int i=0;i<1000;++i)st.push(i);for(int i=0;i<1000;++i)if(!st.empty())st.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkQueue(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::queue<int> q;while(true){for(int i=0;i<1000;++i)q.push(i);for(int i=0;i<1000;++i)if(!q.empty())q.pop();c+=1000;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDFS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>> adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back(rng()%V);while(true){std::vector<bool> vis(V,false);std::stack<int> stk;stk.push(0);while(!stk.empty()){int u=stk.top();stk.pop();if(!vis[u]){vis[u]=true;c++;for(int v:adj[u])if(!vis[v])stk.push(v);}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkBFS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=100;std::vector<std::vector<int>> adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back(rng()%V);while(true){std::vector<bool> vis(V,false);std::queue<int> q;q.push(0);vis[0]=true;while(!q.empty()){int u=q.front();q.pop();c++;for(int v:adj[u])if(!vis[v]){vis[v]=true;q.push(v);}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkDijkstra(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=50;std::vector<std::vector<std::pair<int,int>>> adj(V);std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<5;++j)adj[i].push_back({rng()%V,rng()%100});while(true){std::vector<int> dist(V,INT_MAX);std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;dist[0]=0;pq.push({0,0});while(!pq.empty()){int u=pq.top().second;pq.pop();for(auto&e:adj[u]){int v=e.first,w=e.second;if(dist[u]+w<dist[v]){dist[v]=dist[u]+w;pq.push({dist[v],v});c++;}}}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkFloyd(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int V=50;std::vector<std::vector<int>> dist(V,std::vector<int>(V,999));std::mt19937 rng(1);for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(i!=j)dist[i][j]=rng()%100;while(true){for(int k=0;k<V;++k)for(int i=0;i<V;++i)for(int j=0;j<V;++j)if(dist[i][j]>dist[i][k]+dist[k][j])dist[i][j]=dist[i][k]+dist[k][j];c+=V*V*V;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkKnapsack(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;const int N=100,W=100;std::vector<int> wt(N,1),val(N,1);std::vector<std::vector<int>> K(N+1,std::vector<int>(W+1,0));while(true){for(int i=0;i<=N;++i)for(int w=0;w<=W;++w){if(i==0||w==0)K[i][w]=0;else if(wt[i-1]<=w)K[i][w]=std::max(val[i-1]+K[i-1][w-wt[i-1]],K[i-1][w]);else K[i][w]=K[i-1][w];c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkLCS(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string X="ABCBDAB",Y="BDCABA";int m=X.size(),n=Y.size();std::vector<std::vector<int>> L(m+1,std::vector<int>(n+1,0));while(true){for(int i=0;i<=m;++i)for(int j=0;j<=n;++j){if(i==0||j==0)L[i][j]=0;else if(X[i-1]==Y[j-1])L[i][j]=L[i-1][j-1]+1;else L[i][j]=std::max(L[i-1][j],L[i][j-1]);c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkEditDist(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::string s1="kitten",s2="sitting";int m=s1.size(),n=s2.size();std::vector<std::vector<int>> dp(m+1,std::vector<int>(n+1,0));while(true){for(int i=0;i<=m;++i)for(int j=0;j<=n;++j){if(i==0)dp[i][j]=j;else if(j==0)dp[i][j]=i;else if(s1[i-1]==s2[j-1])dp[i][j]=dp[i-1][j-1];else dp[i][j]=1+std::min({dp[i][j-1],dp[i-1][j],dp[i-1][j-1]});c++;}if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}
long long benchmarkPrimeFact(int d){auto t=std::chrono::high_resolution_clock::now();long long c=0;std::mt19937 rng(1);while(true){long long n=rng()%1000000;for(long long i=2;i*i<=n;++i)while(n%i==0){n/=i;c++;}if(n>1)c++;if(std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t).count()>=d)break;}return c;}

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
    int wComboCpuA = (int)(450 * escala); 
    int wComboCpuB = (int)(450 * escala);
    
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
    colocarPar(hStaticCpuA, hComboCpuA, traducoes[currentLangIndex].labelCpuA, wComboCpuA);
    colocarPar(hStaticCpuB, hComboCpuB, traducoes[currentLangIndex].labelCpuB, wComboCpuB);
    
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
    if (alturaLog < 200) alturaLog = 200;
    if (hEditLog) MoveWindow(hEditLog, 15, y, g_winW - 30, alturaLog, TRUE);
}

void AtualizarFontesSimples(int fontSize) {
    currentFontSize = fontSize;
    if (hFontAtual) DeleteObject(hFontAtual);
    hFontAtual = CreateFontW(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
    
    HWND controles[] = {hStaticLang, hComboLang, hStaticFont, hComboFont,
                        hStaticCompare, hComboCompare, hStaticCpuA, hComboCpuA,
                        hStaticCpuB, hComboCpuB, hBtnRun, hStaticStatus};
    for (HWND h : controles) {
        if (h) SendMessageW(h, WM_SETFONT, (WPARAM)hFontAtual, TRUE);
    }
    
    if (hEditLog) {
        CHARFORMAT2W cf = {0};
        cf.cbSize = sizeof(cf);
        cf.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR | CFM_BOLD;
        cf.yHeight = fontSize * 10;
        wcscpy_s(cf.szFaceName, L"Consolas");
        cf.crTextColor = RGB(0, 0, 0);
        cf.dwEffects = CFE_BOLD;
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
    SetWindowTextW(hStaticCpuA, traducoes[langIndex].labelCpuA);
    SetWindowTextW(hStaticCpuB, traducoes[langIndex].labelCpuB);
    if (GetWindowTextLengthW(hStaticStatus) > 0)
        SetWindowTextW(hStaticStatus, traducoes[langIndex].statusPronto);
    if (pcsCadastrados.size() > 0)
        pcsCadastrados[0].nome = traducoes[langIndex].selecionePC;
    AtualizarListaComparacao();
    AtualizarPainelPrincipal();
    PosicionarControlesTopo();
}

void AtualizarListaComparacao() {
    SendMessageW(hComboCompare, CB_RESETCONTENT, 0, 0);
    if (hComboCpuA) SendMessageW(hComboCpuA, CB_RESETCONTENT, 0, 0);
    if (hComboCpuB) SendMessageW(hComboCpuB, CB_RESETCONTENT, 0, 0);
    if (pcsCadastrados.empty()) return;
    std::vector<size_t> indices;
    for (size_t i = 1; i < pcsCadastrados.size(); ++i) indices.push_back(i);
    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        return pcsCadastrados[a].totalMultiCore > pcsCadastrados[b].totalMultiCore;
    });
    auto popularCombo = [&](HWND combo) {
        if (!combo) return;
        int p = (int)SendMessageW(combo, CB_ADDSTRING, 0, (LPARAM)pcsCadastrados[0].nome.c_str());
        SendMessageW(combo, CB_SETITEMDATA, p, (LPARAM)0);
        for (size_t idx : indices) {
            p = (int)SendMessageW(combo, CB_ADDSTRING, 0, (LPARAM)pcsCadastrados[idx].nome.c_str());
            SendMessageW(combo, CB_SETITEMDATA, p, (LPARAM)idx);
        }
        SendMessageW(combo, CB_SETCURSEL, 0, 0);
    };
    popularCombo(hComboCompare);
    popularCombo(hComboCpuA);
    popularCombo(hComboCpuB);
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
        g_cabecalhoAtual = cabecalho;
        g_modoCpuXCpuAtivo = false;
    }
    logText += L"-----------------------------------------------------------------------\r\n";
    for (int i = 0; i < 100; ++i) {
        wchar_t linha[512];
        const wchar_t* nomeTeste = nomesTestesPT[i];
        if (temComparacao) {
            double diff = 0.0;
            if (pcsCadastrados[comboIndex].scoresMultiCore[i] > 0)
                diff = ((meuUltimoScoreTestsMulti[i] - pcsCadastrados[comboIndex].scoresMultiCore[i]) / pcsCadastrados[comboIndex].scoresMultiCore[i]) * 100.0;
            swprintf_s(linha, L"%-35s | %12.1f | %12.1f | %9.1f%%\r\n", nomeTeste, meuUltimoScoreTestsMulti[i], pcsCadastrados[comboIndex].scoresMultiCore[i], diff);
        } else {
            swprintf_s(linha, L"%-35s | %12.1f\r\n", nomeTeste, meuUltimoScoreTestsMulti[i]);
        }
        logText += linha;
    }
    wchar_t total[256];
    double diffTotalMulti = 0.0;
    if (temComparacao) {
        if (pcsCadastrados[comboIndex].totalMultiCore > 0)
            diffTotalMulti = ((meuUltimoTotalMulti - pcsCadastrados[comboIndex].totalMultiCore) / pcsCadastrados[comboIndex].totalMultiCore) * 100.0;
        swprintf_s(total, L"\r\n%s: %.1f PTS | %.1f PTS | %.1f%%\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalMulti, pcsCadastrados[comboIndex].totalMultiCore, diffTotalMulti);
    } else {
        swprintf_s(total, L"\r\n%s: %.1f PTS\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalMulti);
    }
    logText += total;
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
        const wchar_t* nomeTeste = nomesTestesPT[i];
        if (temComparacao) {
            double diff = 0.0;
            if (pcsCadastrados[comboIndex].scoresSingleCore[i] > 0)
                diff = ((meuUltimoScoreTestsSingle[i] - pcsCadastrados[comboIndex].scoresSingleCore[i]) / pcsCadastrados[comboIndex].scoresSingleCore[i]) * 100.0;
            swprintf_s(linha, L"%-35s | %12.1f | %12.1f | %9.1f%%\r\n", nomeTeste, meuUltimoScoreTestsSingle[i], pcsCadastrados[comboIndex].scoresSingleCore[i], diff);
        } else {
            swprintf_s(linha, L"%-35s | %12.1f\r\n", nomeTeste, meuUltimoScoreTestsSingle[i]);
        }
        logText += linha;
    }
    double diffTotalSingle = 0.0;
    if (temComparacao) {
        if (pcsCadastrados[comboIndex].totalSingleCore > 0)
            diffTotalSingle = ((meuUltimoTotalSingle - pcsCadastrados[comboIndex].totalSingleCore) / pcsCadastrados[comboIndex].totalSingleCore) * 100.0;
        swprintf_s(total, L"\r\n%s: %.1f PTS | %.1f PTS | %.1f%%\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalSingle, pcsCadastrados[comboIndex].totalSingleCore, diffTotalSingle);
    } else {
        swprintf_s(total, L"\r\n%s: %.1f PTS\r\n", traducoes[currentLangIndex].compTotal, meuUltimoTotalSingle);
    }
    logText += total;
    logText += L"\r\n=================================================================\r\n";
    if (temComparacao) {
        double diffFinal = diffTotalMulti;
        if (diffFinal > 0) {
            logText += L"\r\n"; logText += traducoes[currentLangIndex].msgMaisRapido;
            wchar_t buf[100]; swprintf_s(buf, L"%.1f%%) ***\r\n", diffFinal); logText += buf;
        } else if (diffFinal < 0) {
            logText += L"\r\n"; logText += traducoes[currentLangIndex].msgMaisLento;
            wchar_t buf[100]; swprintf_s(buf, L"%.1f%%) ***\r\n", diffFinal); logText += buf;
        } else {
            logText += L"\r\n"; logText += traducoes[currentLangIndex].msgEmpate; logText += L"\r\n";
        }
    } else {
        logText += L"\r\n"; logText += traducoes[currentLangIndex].msgSelecioneParaComparar; logText += L"\r\n";
    }
    logText += L"=================================================================\r\n";
    SetWindowTextW(hEditLog, logText.c_str());
}

void AtualizarPainelComparativoCpuXCpu(int idxA, int idxB) {
    if (idxA <= 0 || idxB <= 0 || idxA >= (int)pcsCadastrados.size() || idxB >= (int)pcsCadastrados.size() || idxA == idxB) return;
    const PCReferencia& a = pcsCadastrados[idxA];
    const PCReferencia& b = pcsCadastrados[idxB];
    
    std::wstring nomeAcurto = TruncarTexto(a.nome, 55);
    std::wstring nomeBcurto = TruncarTexto(b.nome, 55);
    
    std::wstring logText = L"";
    logText += L"===============================================================\r\n";
    logText += traducoes[currentLangIndex].headerResult;
    logText += L"\r\n===============================================================\r\n\r\n";
    for (int secao = 0; secao < 2; ++secao) {
        bool multi = (secao == 0);
        logText += multi ? traducoes[currentLangIndex].compMultiCore : traducoes[currentLangIndex].compSingleCore;
        logText += L"\r\n";
        {
            wchar_t cabecalho[512];
            swprintf_s(cabecalho, L"%-35s | %55.55s | %55.55s | %10s\r\n", 
                       traducoes[currentLangIndex].colTeste, nomeAcurto.c_str(), nomeBcurto.c_str(), traducoes[currentLangIndex].colDif);
            logText += cabecalho;
            if (secao == 0) {
                g_cabecalhoAtual = cabecalho;
                g_modoCpuXCpuAtivo = true;
            }
        }
        logText += L"---------------------------------------------------------------------------------------------------------------------------\r\n";
        const double* scoresA = multi ? a.scoresMultiCore : a.scoresSingleCore;
        const double* scoresB = multi ? b.scoresMultiCore : b.scoresSingleCore;
        for (int i = 0; i < 100; ++i) {
            wchar_t linha[512];
            const wchar_t* nomeTeste = nomesTestesPT[i];
            double diff = 0.0;
            if (scoresA[i] > 0) diff = ((scoresB[i] - scoresA[i]) / scoresA[i]) * 100.0;
            swprintf_s(linha, L"%-35s | %55.1f | %55.1f | %9.1f%%\r\n", nomeTeste, scoresA[i], scoresB[i], diff);
            logText += linha;
        }
        double totalA = multi ? a.totalMultiCore : a.totalSingleCore;
        double totalB = multi ? b.totalMultiCore : b.totalSingleCore;
        double diffTotal = (totalA > 0) ? ((totalB - totalA) / totalA) * 100.0 : 0.0;
        
        wchar_t total[512];
        swprintf_s(total, L"\r\n%-12s %55.1f PTS | %55.1f PTS | %9.1f%%\r\n", 
                   traducoes[currentLangIndex].compTotal, totalA, totalB, diffTotal);
        logText += total;
        logText += L"\r\n";
    }
    logText += L"=================================================================\r\n";
    SetWindowTextW(hEditLog, logText.c_str());
}

void ObterSelecaoCpuXCpu(int& idxA, int& idxB) {
    idxA = -1; idxB = -1;
    if (hComboCpuA) {
        int posA = (int)SendMessageW(hComboCpuA, CB_GETCURSEL, 0, 0);
        if (posA >= 0) idxA = (int)SendMessageW(hComboCpuA, CB_GETITEMDATA, posA, 0);
    }
    if (hComboCpuB) {
        int posB = (int)SendMessageW(hComboCpuB, CB_GETCURSEL, 0, 0);
        if (posB >= 0) idxB = (int)SendMessageW(hComboCpuB, CB_GETITEMDATA, posB, 0);
    }
}

void AtualizarPainelPrincipal() {
    int idxA = -1, idxB = -1;
    ObterSelecaoCpuXCpu(idxA, idxB);
    bool modoCpuXCpu = (idxA > 0 && idxB > 0 && idxA < (int)pcsCadastrados.size() &&
                        idxB < (int)pcsCadastrados.size() && idxA != idxB);
    if (modoCpuXCpu) {
        AtualizarPainelComparativoCpuXCpu(idxA, idxB);
    } else if (benchmarkRealizado) {
        AtualizarPainelComparativo();
    }
}

void ExecutarBenchmarkThread(HWND hwnd, int langIndex) {
    benchmarkEmAndamento = true;
    try {
        EnableWindow(hBtnRun, FALSE);
        EnableWindow(hComboLang, FALSE);
        EnableWindow(hComboCompare, FALSE);
        EnableWindow(hComboFont, FALSE);
        HMENU hMenu = GetSystemMenu(hwnd, FALSE);
        if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
        
        unsigned int numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 4;
        if (numThreads > 4000) numThreads = 4000; 
        
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
                    for (int j = 0; j < 100; ++j) pcsCadastrados[i].scoresMultiCore[j] = meuUltimoScoreTestsMulti[j];
                    novoRecorde = true;
                }
                if (meuUltimoTotalSingle > pcsCadastrados[i].totalSingleCore) {
                    pcsCadastrados[i].totalSingleCore = meuUltimoTotalSingle;
                    for (int j = 0; j < 100; ++j) pcsCadastrados[i].scoresSingleCore[j] = meuUltimoScoreTestsSingle[j];
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
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE);
            EnableWindow(hComboLang, TRUE);
            EnableWindow(hComboCompare, TRUE);
            EnableWindow(hComboFont, TRUE);
            HMENU hMenu = GetSystemMenu(hwnd, FALSE);
            if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
        }
        AtualizarPainelPrincipal();
    } catch (const std::exception& e) {
        MessageBoxW(hwnd, traducoes[langIndex].msgErroBenchmark, traducoes[langIndex].tituloErro, MB_ICONERROR);
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE); EnableWindow(hComboLang, TRUE); EnableWindow(hComboCompare, TRUE); EnableWindow(hComboFont, TRUE);
            HMENU hMenu = GetSystemMenu(hwnd, FALSE); if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
            SetWindowTextW(hStaticStatus, traducoes[langIndex].statusErroBenchmark);
        }
    } catch (...) {
        MessageBoxW(hwnd, traducoes[langIndex].msgErroDesconhecido, traducoes[langIndex].tituloErro, MB_ICONERROR);
        if (IsWindow(hwnd)) {
            EnableWindow(hBtnRun, TRUE); EnableWindow(hComboLang, TRUE); EnableWindow(hComboCompare, TRUE); EnableWindow(hComboFont, TRUE);
            HMENU hMenu = GetSystemMenu(hwnd, FALSE); if (hMenu) EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
            SetWindowTextW(hStaticStatus, traducoes[langIndex].statusErroBenchmark);
        }
    }
    benchmarkEmAndamento = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hMainWnd = hwnd; 
            RECT workArea;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
            int screenW = workArea.right - workArea.left;
            int screenH = workArea.bottom - workArea.top;
            int winW = (1400 < screenW) ? 1400 : screenW;
            int winH = (700 < screenH) ? 700 : screenH;
            SetWindowPos(hwnd, NULL, 0, 0, winW, winH, SWP_NOZORDER);
            g_winW = winW; g_winH = winH;
            
            hStaticLang = CreateWindowW(L"STATIC", L"Idioma:", WS_VISIBLE | WS_CHILD, 15, 15, 60, 25, hwnd, (HMENU)ID_STATIC_LANG, NULL, NULL);
            hComboLang = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 80, 15, 150, 250, hwnd, (HMENU)ID_COMBO_LANG, NULL, NULL);
            hStaticFont = CreateWindowW(L"STATIC", L"Fonte:", WS_VISIBLE | WS_CHILD, 15, 15, 50, 25, hwnd, (HMENU)ID_STATIC_FONT, NULL, NULL);
            hComboFont = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 15, 15, 90, 250, hwnd, (HMENU)ID_COMBO_FONT, NULL, NULL);
            hStaticCompare = CreateWindowW(L"STATIC", L"Comparar:", WS_CHILD, 15, 15, 70, 25, hwnd, (HMENU)ID_STATIC_COMPARE, NULL, NULL);
            hComboCompare = CreateWindowW(L"COMBOBOX", L"", WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 15, 15, 280, 250, hwnd, (HMENU)ID_COMBO_PC_COMPARE, NULL, NULL);
            hStaticCpuA = CreateWindowW(L"STATIC", L"CPU A:", WS_VISIBLE | WS_CHILD, 15, 15, 60, 25, hwnd, (HMENU)ID_STATIC_CPU_A, NULL, NULL);
            hComboCpuA = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 15, 15, 220, 250, hwnd, (HMENU)ID_COMBO_CPU_A, NULL, NULL);
            hStaticCpuB = CreateWindowW(L"STATIC", L"CPU B:", WS_VISIBLE | WS_CHILD, 15, 15, 60, 25, hwnd, (HMENU)ID_STATIC_CPU_B, NULL, NULL);
            hComboCpuB = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 15, 15, 220, 250, hwnd, (HMENU)ID_COMBO_CPU_B, NULL, NULL);
            hBtnRun = CreateWindowW(L"BUTTON", L"Iniciar", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 15, 15, 90, 30, hwnd, (HMENU)ID_BTN_RUN, NULL, NULL);
            hStaticStatus = CreateWindowW(L"STATIC", L"Pronto para iniciar.", WS_VISIBLE | WS_CHILD, 15, 55, winW - 30, 25, hwnd, (HMENU)ID_STATIC_STATUS, NULL, NULL);
            
            hEditLog = CreateWindowW(L"RICHEDIT50W", L"",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY | WS_VSCROLL | WS_HSCROLL,
                                     15, 85, winW - 30, winH - 100, hwnd, (HMENU)ID_EDIT_LOG, NULL, NULL);
            SendMessageW(hEditLog, EM_EXLIMITTEXT, 0, (LPARAM)(1024 * 1024));
            SendMessageW(hEditLog, EM_SETBKGNDCOLOR, 0, RGB(255, 255, 255));
            CHARFORMAT2W cfInit = {0};
            cfInit.cbSize = sizeof(cfInit);
            cfInit.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR | CFM_BOLD;
            cfInit.yHeight = 21 * 10;
            wcscpy_s(cfInit.szFaceName, L"Consolas");
            cfInit.crTextColor = RGB(0, 0, 0); 
            cfInit.dwEffects = CFE_BOLD;
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
            AtualizarListaComparacao();
            AtualizarPainelPrincipal();
            break;
        }
        case WM_SYSCOMMAND:
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
        case WM_NOTIFY: {
            NMHDR* pHdr = (NMHDR*)lParam;
            if (pHdr->hwndFrom == hEditLog && pHdr->code == EN_MSGFILTER) {
                MSGFILTER* pFilter = (MSGFILTER*)lParam;
                if (pFilter->msg == WM_MOUSEWHEEL || pFilter->msg == WM_VSCROLL || pFilter->msg == WM_KEYDOWN) {
                    DefWindowProcW(hwnd, uMsg, wParam, lParam);
                    
                    SCROLLINFO si = { sizeof(si), SIF_POS };
                    GetScrollInfo(hEditLog, SB_VERT, &si);
                    
                    if (si.nPos > 0 && !g_cabecalhoAtual.empty()) {
                        POINT pt = {0, 0};
                        LONG firstVisible = (LONG)SendMessageW(hEditLog, EM_CHARFROMPOS, 0, (LPARAM)&pt);
                        LONG lineIdx = (LONG)SendMessageW(hEditLog, EM_LINEFROMCHAR, firstVisible, 0);
                        
                        int len = (int)SendMessageW(hEditLog, EM_LINELENGTH, (WPARAM)firstVisible, 0);
                        if (len > 0) {
                            std::wstring lineText(len, L'\0');
                            *((WORD*)&lineText[0]) = (WORD)len;
                            SendMessageW(hEditLog, EM_GETLINE, lineIdx, (LPARAM)&lineText[0]);
                            
                            if (lineText.find(traducoes[currentLangIndex].colTeste) == std::wstring::npos) {
                                LONG charPos = (LONG)SendMessageW(hEditLog, EM_LINEINDEX, lineIdx, 0);
                                SendMessageW(hEditLog, EM_SETSEL, charPos, charPos);
                                std::wstring insertTxt = g_cabecalhoAtual + L"---------------------------------------------------------------------------------------------------------------------------\r\n";
                                SendMessageW(hEditLog, EM_REPLACESEL, FALSE, (LPARAM)insertTxt.c_str());
                                SendMessageW(hEditLog, EM_LINESCROLL, 0, 2);
                            }
                        }
                    }
                    return 0;
                }
            }
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_COMBO_LANG && HIWORD(wParam) == CBN_SELCHANGE) {
                int langIdx = (int)SendMessageW(hComboLang, CB_GETCURSEL, 0, 0);
                if (langIdx >= 0 && langIdx < 12) AtualizarIdiomaInterface(langIdx);
            }
            else if (LOWORD(wParam) == ID_COMBO_FONT && HIWORD(wParam) == CBN_SELCHANGE) {
                int fontIdx = (int)SendMessageW(hComboFont, CB_GETCURSEL, 0, 0);
                int sizes[] = {18, 21, 27, 33};
                if (fontIdx >= 0 && fontIdx < 4) AtualizarFontesSimples(sizes[fontIdx]);
            }
            else if (LOWORD(wParam) == ID_COMBO_PC_COMPARE && HIWORD(wParam) == CBN_SELCHANGE) {
                AtualizarPainelPrincipal();
            }
            else if (LOWORD(wParam) == ID_COMBO_CPU_A && HIWORD(wParam) == CBN_SELCHANGE) {
                AtualizarPainelPrincipal();
            }
            else if (LOWORD(wParam) == ID_COMBO_CPU_B && HIWORD(wParam) == CBN_SELCHANGE) {
                AtualizarPainelPrincipal();
            }
            else if (LOWORD(wParam) == ID_BTN_RUN && HIWORD(wParam) == BN_CLICKED) {
                int langIdx = (int)SendMessageW(hComboLang, CB_GETCURSEL, 0, 0);
                if (langIdx < 0 || langIdx >= 12) langIdx = 0;
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