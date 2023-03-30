#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
// состоянияя
// F - конец лексемы,Start - начальное состояние автомата
// Ident1,Ident2 - идентификаторы и ключевые слова
// Constant - константы
// Arif - арифметические операции
// Comp,Comp2 - Сравнение
// Eq - равенство
// Space - разделитель
enum EState { F, Start, Ident1, Ident2, Constant, Arif, Comp, Comp2, Eq, E, Space };

enum ELexType { lWh = 0, lCo, lAo, lEq, lId, lVl, lWl, lDo, lLp }; // тип лексемы

enum signals { sign_0, sign_er, sign_dight, sign_alpha, sign_space, sign_arif, sign_ravn, sign_comp }; // символы

enum SState { S, Wh, Do, SEq, Co, Lp, Ao, Id1, Id2, Wl, Vl1, Vl2, Bl1, Bl2 };

struct Lex // структура лексемы
{
    char* firstsign; // указатель на 1 элемент
    int lenght; // длина лексемы
    ELexType type; // тип лексемы
};

void createtableLex(SState(*table)[9])
{
    table[S][lWh] = Wl;
    table[S][lCo] = Wl;
    table[S][lAo] = Wl;
    table[S][lEq] = Wl;
    table[S][lId] = Wl;
    table[S][lWl] = Wl;
    table[S][lVl] = Wl;
    table[S][lDo] = Do;
    table[S][lLp] = Wl;

    table[Wh][lWh] = Wl;
    table[Wh][lCo] = Wl;
    table[Wh][lAo] = Wl;
    table[Wh][lEq] = Wl;
    table[Wh][lId] = Bl1;
    table[Wh][lWl] = Wl;
    table[Wh][lVl] = Bl1;
    table[Wh][lDo] = Wl;
    table[Wh][lLp] = Wl;

    table[Bl1][lWh] = Wl;
    table[Bl1][lCo] = Co;
    table[Bl1][lAo] = Wl;
    table[Bl1][lEq] = Co;
    table[Bl1][lId] = Id1;
    table[Bl1][lWl] = Wl;
    table[Bl1][lVl] = Wl;
    table[Bl1][lDo] = Wl;
    table[Bl1][lLp] = Wl;

    table[Bl2][lWh] = Wl;
    table[Bl2][lCo] = Wl;
    table[Bl2][lAo] = Wl;
    table[Bl2][lEq] = Wl;
    table[Bl2][lId] = Id1;
    table[Bl2][lWl] = Wl;
    table[Bl2][lVl] = Wl;
    table[Bl2][lDo] = Wl;
    table[Bl2][lLp] = Wl;

    table[Id1][lWh] = Wl;
    table[Id1][lCo] = Wl;
    table[Id1][lAo] = Ao;
    table[Id1][lEq] = SEq;
    table[Id1][lId] = Wl;
    table[Id1][lWl] = Wl;
    table[Id1][lVl] = Wl;
    table[Id1][lDo] = Wl;
    table[Id1][lLp] = Wl;

    table[Id2][lWh] = Wl;
    table[Id2][lCo] = Wl;
    table[Id2][lAo] = Ao;
    table[Id2][lEq] = Wl;
    table[Id2][lId] = Wl;
    table[Id2][lWl] = Wl;
    table[Id2][lVl] = Wl;
    table[Id2][lDo] = Wl;
    table[Id2][lLp] = Lp;

    table[Vl1][lWh] = Wl;
    table[Vl1][lCo] = Co;
    table[Vl1][lAo] = Ao;
    table[Vl1][lEq] = SEq;
    table[Vl1][lId] = Wl;
    table[Vl1][lWl] = Wl;
    table[Vl1][lVl] = Wl;
    table[Vl1][lDo] = Wl;
    table[Vl1][lLp] = Wl;

    table[Vl2][lWh] = Wl;
    table[Vl2][lCo] = Wl;
    table[Vl2][lAo] = Ao;
    table[Vl2][lEq] = Wl;
    table[Vl2][lId] = Wl;
    table[Vl2][lWl] = Wl;
    table[Vl2][lVl] = Wl;
    table[Vl2][lDo] = Wl;
    table[Vl2][lLp] = Lp;

    table[Co][lWh] = Wl;
    table[Co][lCo] = Wl;
    table[Co][lAo] = Wl;
    table[Co][lEq] = Wl;
    table[Co][lId] = Bl2;
    table[Co][lWl] = Wl;
    table[Co][lVl] = Bl2;
    table[Co][lDo] = Wl;
    table[Co][lLp] = Wl;

    table[Ao][lWh] = Wl;
    table[Ao][lCo] = Wl;
    table[Ao][lAo] = Wl;
    table[Ao][lEq] = Wl;
    table[Ao][lId] = Id2;
    table[Ao][lWl] = Wl;
    table[Ao][lVl] = Vl2;
    table[Ao][lDo] = Wl;
    table[Ao][lLp] = Wl;

    table[SEq][lWh] = Wl;
    table[SEq][lCo] = Wl;
    table[SEq][lAo] = Wl;
    table[SEq][lEq] = Wl;
    table[SEq][lId] = Id2;
    table[SEq][lWl] = Wl;
    table[SEq][lVl] = Vl2;
    table[SEq][lDo] = Wl;
    table[SEq][lLp] = Wl;

    table[Do][lWh] = Wh;
    table[Do][lCo] = Wl;
    table[Do][lAo] = Wl;
    table[Do][lEq] = Wl;
    table[Do][lId] = Wl;
    table[Do][lWl] = Wl;
    table[Do][lVl] = Wl;
    table[Do][lDo] = Wl;
    table[Do][lLp] = Wl;

    table[Lp][lWh] = Wl;
    table[Lp][lCo] = Wl;
    table[Lp][lAo] = Wl;
    table[Lp][lEq] = Wl;
    table[Lp][lId] = Wl;
    table[Lp][lWl] = Wl;
    table[Lp][lVl] = Wl;
    table[Lp][lDo] = Do;
    table[Lp][lLp] = Wl;
}

void createtable(EState(*table)[8]) // заполнение матрицы переходов
{
    table[F][sign_er] = F;
    table[F][sign_dight] = F;
    table[F][sign_alpha] = F;
    table[F][sign_space] = F;
    table[F][sign_arif] = F;
    table[F][sign_ravn] = F;
    table[F][sign_comp] = F;
    table[F][sign_0] = F;

    table[Start][sign_er] = E;
    table[Start][sign_dight] = Constant;
    table[Start][sign_alpha] = Ident1;
    table[Start][sign_space] = Space;
    table[Start][sign_arif] = Arif;
    table[Start][sign_ravn] = Eq;
    table[Start][sign_comp] = Comp;
    table[Start][sign_0] = F;

    table[Space][sign_er] = E;
    table[Space][sign_dight] = Start;
    table[Space][sign_alpha] = Start;
    table[Space][sign_space] = Start;
    table[Space][sign_arif] = Start;
    table[Space][sign_ravn] = Start;
    table[Space][sign_comp] = Start;
    table[Space][sign_0] = F;

    table[Ident1][sign_er] = E;
    table[Ident1][sign_dight] = Ident2;
    table[Ident1][sign_alpha] = Ident2;
    table[Ident1][sign_space] = Start;
    table[Ident1][sign_arif] = Start;
    table[Ident1][sign_ravn] = Start;
    table[Ident1][sign_comp] = Start;
    table[Ident1][sign_0] = F;

    table[Ident2][sign_er] = E;
    table[Ident2][sign_dight] = Ident2;
    table[Ident2][sign_alpha] = Ident2;
    table[Ident2][sign_space] = Start;
    table[Ident2][sign_arif] = Start;
    table[Ident2][sign_ravn] = Start;
    table[Ident2][sign_comp] = Start;
    table[Ident2][sign_0] = F;

    table[Constant][sign_er] = E;
    table[Constant][sign_dight] = Constant;
    table[Constant][sign_alpha] = E;
    table[Constant][sign_space] = Start;
    table[Constant][sign_arif] = Start;
    table[Constant][sign_ravn] = Start;
    table[Constant][sign_comp] = Start;
    table[Constant][sign_0] = F;

    table[Arif][sign_er] = E;
    table[Arif][sign_dight] = Start;
    table[Arif][sign_alpha] = Start;
    table[Arif][sign_space] = Start;
    table[Arif][sign_arif] = Start;
    table[Arif][sign_ravn] = Start;
    table[Arif][sign_comp] = Start;
    table[Arif][sign_0] = F;

    table[Comp][sign_er] = E;
    table[Comp][sign_dight] = Start;
    table[Comp][sign_alpha] = Start;
    table[Comp][sign_space] = Start;
    table[Comp][sign_arif] = Start;
    table[Comp][sign_ravn] = Comp2;
    table[Comp][sign_comp] = Start;
    table[Comp][sign_0] = F;

    table[Comp2][sign_er] = E;
    table[Comp2][sign_dight] = Start;
    table[Comp2][sign_alpha] = Start;
    table[Comp2][sign_space] = Start;
    table[Comp2][sign_arif] = Start;
    table[Comp2][sign_ravn] = Start;
    table[Comp2][sign_comp] = Start;
    table[Comp2][sign_0] = F;

    table[Eq][sign_er] = E;
    table[Eq][sign_dight] = Start;
    table[Eq][sign_alpha] = Start;
    table[Eq][sign_space] = Start;
    table[Eq][sign_arif] = Start;
    table[Eq][sign_ravn] = Start;
    table[Eq][sign_comp] = Start;
    table[Eq][sign_0] = F;

    table[E][sign_er] = E;
    table[E][sign_dight] = E;
    table[E][sign_alpha] = E;
    table[E][sign_space] = Start;
    table[E][sign_arif] = Start;
    table[E][sign_ravn] = Start;
    table[E][sign_comp] = Start;
    table[E][sign_0] = F;
}


signals check(const char c) // проверка символов
{
    if ('0' <= c && c <= '9') return sign_dight;
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) return sign_alpha;
    if (c == ' ' || c == '\t' || c == '\n') return sign_space;
    if (c == '+' || c == '-') return sign_arif;
    if (c == '=') return sign_ravn;
    if (c == '<' || c == '>') return sign_comp;
    if (c == '\0') return sign_0;

    return sign_er;
}


int check_kw(const char* c, int size)// проверка лексемы на совпадение с ключевым словомм
{
    char* c_copy = new char[size + 1];
    strncpy_s(&c_copy[0], size + 1, c, size);
    char* p = &c_copy[0];
    p += size;
    *p = '\0';

    if (!strcmp(c_copy, "do")) { delete[] c_copy; return 3; }
    if (!strcmp(c_copy, "while")) { delete[] c_copy; return 2; }
    if (!strcmp(c_copy, "loop")) { delete[] c_copy; return 1; }

    delete[] c_copy;
    return 0;
}


ELexType checktype(char* c, int size, EState state) // выбор типа лексемы
{
    int kw = check_kw(c, size);
    if (kw == 3) return lDo;
    if (kw == 2) return lWh;
    if (kw == 1) return lLp;
    if (state == Comp || state == Comp2) return lCo;
    if (state == Arif) return lAo;
    if (state == Eq) return lEq;
    if (Ident1 <= state && state <= Ident2 && size <= 5) return lId;
    if (state == Constant && -32768 <= atoi(c) && atoi(c) <= 32767) return lVl;
    return lWl;

}


void processtext(char* text, EState(*table)[8], vector<Lex>& result) // обработка строки
{
    int lenght = 0;
    EState curstate = Start; // начальное состояние
    Lex Item;

    while (curstate != F) // пока не '\0'
    {

        if (table[curstate][check(*text)] == Start || (table[curstate][check(*text)] == F && lenght != 0)) // проверка на то является ли следующий символ разделителем или концом строки
        {

            Item.firstsign = (text - lenght);
            Item.lenght = lenght;
            Item.type = checktype(text - lenght, lenght, curstate);
            result.push_back(Item);

            lenght = 0;
            curstate = table[curstate][check(*text)];
            if (curstate == E)
                curstate = Start;
        }
        else
        {

            curstate = table[curstate][check(*text)];
            text++;
            lenght++;
            if (curstate == Space)
            {
                curstate = Start;
                lenght = 0;
            }
        }
    }
}


void print_elextype(ELexType type, ofstream& out) // вывод типа лексемы в файл
{
    if (type == lWh) { out << "wh"; return; }
    if (type == lDo) { out << "do"; return; }
    if (type == lLp) { out << "lp"; return; }
    if (type == lCo) { out << "co"; return; }

    if (type == lAo) { out << "ao"; return; }
    if (type == lEq) { out << "eq"; return; }
    if (type == lId) { out << "id"; return; }
    if (type == lVl) { out << "vl"; return; }
    out << "wl";
}

int checkLex(vector<Lex>& lexs, SState& curectstate, SState(*tabelLex)[9])
{
    long unsigned int i;
    for (i = 0; i < lexs.size(); i++)
    {
        if (tabelLex[curectstate][lexs[i].type] == Wl)
            return i;
        curectstate = tabelLex[curectstate][lexs[i].type];
    }
    if (curectstate == Lp)
        return -1;
    return i;
}


void print(vector<Lex>& result, int err, SState& curectstate, SState (*curlex)[9])
{
    ofstream fout("output.txt"); // открытие файла для записи
    if (result.size()) // проверка на то не пуст ли вектор
    {
        for (unsigned int i = 0; i < result.size(); i++) // вывод лексем и их типов
        {
            for (int j = 0; j < result[i].lenght; j++)
                fout << *(result[i].firstsign + j); // вывод лексемы по символу

            fout << '['; print_elextype(result[i].type, fout);  fout << ']' << ' ';


        }

        fout << '\n';
        if (err != -1)
        {

            fout << err << ' ';
            for (int i = 0; i < 9; i++)
            {
                if (curlex[curectstate][static_cast<ELexType>(i)] != Wl)
                {
                    print_elextype(static_cast<ELexType>(i), fout);
                    fout << ' ';
                }
            }


        }
        else
            fout << "OK";
    }
    fout.close(); // закрытие выходного файла

}


int main()
{
    ifstream fin("input.txt"); // открытие входного файла

    long long int size = 0;

    fin.seekg(0, ios::end); // переставление на конец
    size = fin.tellg(); // вычисление размера
    fin.seekg(0, ios::beg); // возвращение указателя на начало файла
    char* text = new char[size + 1]; // выделение памяти под текст
    fin.getline(text, size + 1, '\0'); // считывание из файла
    fin.close(); // закрытие входного файла

    EState current_table[11][8]; // матрица состояний
    createtable(current_table); // создание матрицы
    vector<Lex> result; // вектор лексем
    processtext(text, current_table, result); // обработка лексем
    SState curectstate = S;
    SState tabelLex[14][9];
    createtableLex(tabelLex);
    int err = checkLex(result, curectstate, tabelLex);
    print(result, err, curectstate, tabelLex); // вывод всей необходимой информации


    delete[] text; // очищение динамически выделенной помяти
    return 0;
}
