//Разработать  программу  -  32-разрядное  приложение  для  ОС
//Windows,  -  демонстрирующую  возможности  языка C++, а также его
//стандартной  библиотеки  по  работе  с  потоками,  контейнерами и
//итераторами.
//Использование   всех  вышеупомянутых  возможностей  является
//обязательным в каждом из вариантов индивидуальных заданий.
//В каждом из нижеуказанных вариантов задания ВАМИ должны быть
//реализованы основные возможножности библиотеки стандартных шаблонов:
//итератор(ы), поиск, упорядочение, сумма или что-то аналогичное по
//согласованию с преподавателем.
//
//5.(17.3)  Напишите  программу, которая заносила бы различные
//слова  в  файл в алфавитном порядке. Сделайте две версии: пусть в
//одной   слово   будет  просто  последовательностью  символов,  не
//содержащей    символов    -    разделителей,    а    в   другой -
//последовательностью символов, не содержащей символов-небукв.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "my_vector.h"

using namespace std;

bool contains_non_characters(string s){
//    cout << "scanning word " << s << endl;
    int s_len = s.length();
    for(int i = 0; i < s_len; i++){
        char &c = s[i];
        int t = (int)c;
//        cout << c << " - " << t << endl;
        if (!((t >= 65 && t <= 90) || (t >= 97 && t <= 122))) {
//            cout << "found !!" << endl;
            return true;
        }
    }
//    cout << "non-characters not found " << endl;
    return false;
}

int main (int argc, char * const argv[]) {
    bool use_non_characters = false;
//    cout << "use non-characters?:";
//    char c[2]; 
//    cin >> c;
//    if (c[0] == 'y') use_non_characters = true;
    
    
    char filename[] = "words.txt";
//    vector<string> lines;
    MyVector<string> lines;
    cout << "reading words from " << filename << endl;
    ifstream data_in(filename, ios_base::in);
    while(!data_in.eof()){
        string tmp_line;
        getline(data_in,tmp_line);
        //lines.push_back(tmp_line);
        lines.add(tmp_line);
    }
    data_in.close();
    
    cout << "readed words: " << endl;
//    for (vector<string>::iterator it=lines.begin(); it < lines.end(); it++) {
    for (MyVector<string>::iterator it=lines.begin(); it < lines.end(); it++) {
        cout << *it << endl;
        if (contains_non_characters(*it) && !use_non_characters) {
            cout << "contains non characters... aborting program" << endl;
            return 0;
        }
    }
    cout << endl;
    cout << "input words(to exit type enter):" << endl;
    string line;
    while (getline(cin,line) && line != "exit"){
//        cout << "contains non-characters : " << contains_non_characters(line) << endl;
        if (!use_non_characters && contains_non_characters(line)) {
            cout << "containst non-characters, ignoring word" << endl;
            continue;
        }
        for (MyVector<string>::iterator it=lines.begin(); it < lines.end(); it++) {
            if (line.compare(*it) < 0){
                lines.insert(*it, line);
                break;
            }
        }
    }
    cout << "words input ended" << endl;
    
    cout << "result list: " << endl;
    for (MyVector<string>::iterator it=lines.begin(); it < lines.end(); it++)
        cout << *it << endl;
    //записывам список обратно в файл
//    ofstream data_out(filename, ios_base::out | ios_base::trunc);
//    for (vector<string>::iterator it=lines.begin(); it < lines.end(); it++)
//        data_out << *it << endl;
//    data_out.close();
    return 0;
}
