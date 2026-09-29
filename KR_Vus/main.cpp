// Developed by Pavlo Vus on 16.04.2026
#include <iostream>
#include <cassert>

#include "Dictionary.h"
#include "Word.h"

using namespace std;

static auto LOREM =
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Maecenas porttitor congue massa. "
    "Fusce posuere, magna sed pulvinar ultricies, purus lectus malesuada libero, "
    "sit amet commodo magna eros quis urna. Nunc viverra imperdiet enim. Fusce est. Vivamus a tellus. "
    "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. "
    "Proin pharetra nonummy pede. Mauris et orci. Aenean nec lorem. In porttitor. Donec laoreet nonummy augue. "
    "Suspendisse dui purus, scelerisque at, vulputate vitae, pretium mattis, nunc. "
    "Mauris eget neque at sem venenatis eleifend. Ut nonummy. Fusce aliquet pede non pede. "
    "Suspendisse dapibus lorem pellentesque magna. Integer nulla. "
    "Donec blandit feugiat ligula. Donec hendrerit, felis et imperdiet euismod, purus ipsum pretium metus,"
    "in lacinia nulla nisl eget sapien. Donec ut est in lectus consequat consequat. Etiam eget dui."
    " Aliquam erat volutpat. Sed at lorem in nunc porta tristique. Proin nec augue. Quisque aliquam tempor magna. "
    "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. "
    "Nunc ac magna. Maecenas odio dolor, vulputate vel, auctor ac, accumsan id, felis. Pellentesque cursus sagittis felis.";

// Допоміжний метод для зручного виведення словника разом з назвою та розміром
template<typename T>
void print_dict(const char* name, const Dictionary<T>& d)
{
    cout << name << " (" << d.size() << " слів):\n" << d << "\n\n";
}

// Допоміжний метод для заповнення словника з тексту
int fill_from_text(Dictionary<string>& dict, const char* text)
{
    int count = 0;
    string word;
    for (const char* p = text; *p; ++p) {
        if (const auto c = static_cast<unsigned char>(*p); isalpha(c)) {
            word += static_cast<char>(tolower(c));
        } else if (!word.empty()) {
            ++count;
            dict.insert(word);
            word.clear();
        }
    }
    if (!word.empty()) { ++count; dict.insert(word); }
    return count;
}

int main() {
    using WDict = Dictionary<Word<>>;

    cout << "Заповнюємо словник тестовим текстом\n";
    Dictionary<string> dict;
    const int raw_count = fill_from_text(dict, LOREM);

    cout << "Слів у тексті (з повторами): " << raw_count << "\n";
    cout << "Унікальних слів у словнику:  " << dict.size() << "\n\n";

    assert(raw_count >= 100);
    assert(!dict.empty());
    print_dict("dict", dict);

    assert(dict.is_sorted());
    cout << "dict відсортовано лексикографічно\n\n";

    cout << "Копіювання copy()\n";
    Dictionary<string> dict_copy;
    copy(dict_copy, dict);

    assert(dict_copy == dict);
    assert(dict_copy.size() == dict.size());
    assert(dict_copy.is_sorted());
    cout << "copy(dict_copy, dict): dict_copy == dict\n";
    cout << "dict_copy відсортовано\n\n";

    cout << "Переміщення merge_into()\n";
    Dictionary dict_src(dict);
    Dictionary<string> dict_dst;

    cout << "Перед merge_into: dict_src.size() = " << dict_src.size() << "\n";
    merge_into(dict_dst, std::move(dict_src));
    cout << "Після merge_into: dict_src.size() = " << dict_src.size() << "\n";
    cout << "Після merge_into: dict_dst.size() = " << dict_dst.size() << "\n\n";

    assert(dict_src.empty());
    assert(dict_dst == dict);
    assert(dict_dst.is_sorted());
    cout << "dict_src порожній після переміщення\n";
    cout << "dict_dst == dict\n\n";

    cout << "Транспортування у Dictionary<Word<16>>\n";
    WDict edict;
    for (const auto & it : dict) edict.insert(Word(it));

    assert(edict.size() == dict.size());
    assert(edict.is_sorted());
    cout << "edict.size() == dict.size()\n";
    cout << "edict відсортовано\n";
    print_dict("edict", edict);

    cout << "Непарні та парні позиції\n";
    WDict edict1;
    WDict edict2;

    for (size_t i = 0; i < edict.size(); ++i) {
        if (const size_t pos = i + 1; pos % 2 == 1) edict1.insert(edict[i]);
        else edict2.insert(edict[i]);
    }

    assert(edict1.is_sorted() && edict2.is_sorted());
    cout << "edict1.size() = " << edict1.size() << ",  edict2.size() = " << edict2.size() << "\n";
    print_dict("edict1 (непарні позиції)", edict1);
    print_dict("edict2 (парні позиції)",   edict2);

    WDict union12 = edict1 + edict2;
    assert(union12.is_sorted());
    assert(union12 == edict);
    cout << "edict1 + edict2 == edict\n\n";

    cout << "Позиції кратні 3 та 6\n";
    WDict edict3;
    WDict edict6;

    for (size_t i = 0; i < edict.size(); ++i) {
        const size_t pos = i + 1;
        if (pos % 3 == 0) edict3.insert(edict[i]);
        if (pos % 6 == 0) edict6.insert(edict[i]);
    }

    assert(edict3.is_sorted() && edict6.is_sorted());
    cout << "edict3.size() = " << edict3.size() << ",  edict6.size() = " << edict6.size() << "\n";
    print_dict("edict3 (pos % 3 == 0)", edict3);
    print_dict("edict6 (pos % 6 == 0)", edict6);

    WDict inter23 = edict2 * edict3;
    assert(inter23.is_sorted());
    assert(inter23 == edict6);
    cout << "edict2 * edict3 == edict6\n\n";

    return 0;
}