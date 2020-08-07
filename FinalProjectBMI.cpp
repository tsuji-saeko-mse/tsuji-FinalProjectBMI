// FinalProjectBMI.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<vector>
#include<fstream>
#include<regex>
#include<string>

using namespace std;

//Personクラス
class Person {

    //privateメンバ関数
    string name;       //名前
    double height = 0; //身長
    double weight = 0; //体重
    string gender;     //性別

public:

    void setName(const string& newName) { name = newName; }        //セッタ（名前）
    string getName() { return name; }                              //表示関数（名前）
    void setHeight(double newHeight) { height = newHeight; }       //セッタ（身長）
    double getHeight() { return height; }                          //表示関数（身長）
    void setWeight(double newWeight) { weight = newWeight; }       //セッタ（体重）
    double getWeight() { return weight; }                          //表示関数（体重）
    void setGender(const string& newGender) { gender = newGender; }//セッタ（性別）
    string getGender() { return gender; }                          //表示関数（性別）
};


//文字列をファイルに入力する関数
void InputFile(string& NAMAE, string& SHINCHO, string& TAIJU, string& SEIBETSU) {

    //ofstreamオブジェクトの構築
    ofstream outfile("Body.txt");

    cout << "ようこそ。\nここに身長、体重を入力すると自動でBMIが算出されて、あなたの身体の状態がわかります。\n\n";



NameZone:

    //名前の入力
    cout << "名前を入力して、Enterキーを押してください。(例：山田太郎)\n";
    cin >> NAMAE;



HeightZone:

    //身長の入力
    cout << "身長[cm]を入力して、Enterキーを押してください。（例：180.0）\n";
    cin >> SHINCHO;


    //regexオブジェクトの作成(正規表現の定義)
    regex H1(R"(\d{3}\.\d{1})");//3桁.1桁（小数点以下の入力があるとき）
    regex H2(R"(\d{3})");      //3桁（小数点以下の入力がないとき）
    regex H3(R"(\d{2}\.\d{1})");//2桁.1桁（小数点以下の入力があるとき）
    regex H4(R"(\d{2})");      //2桁（小数点以下の入力がないとき）

    //文字列の形式を確認
    //上記の4種の形式のどれかに当てはまれば、体重入力へ
    if (regex_match(SHINCHO, H1) || regex_match(SHINCHO, H2) || regex_match(SHINCHO, H3) || regex_match(SHINCHO, H4))
        goto WeightZone;

    //当てはまらなければ再度入力（身長入力やり直し）
    else cout << "不正な入力です。再度入力しなおしてください。\n\n";
    goto HeightZone;



WeightZone:

    //体重の入力
    cout << "体重[kg]を入力して、Enterキーを押してください。（例：75.0）\n";
    cin >> TAIJU;

    //regexオブジェクトの作成(正規表現の定義)
    regex W1(R"(\d{3}\.\d{1})");//3桁.1桁（小数点以下の入力があるとき）
    regex W2(R"(\d{3})");      //3桁（小数点以下の入力がないとき）
    regex W3(R"(\d{2}\.\d{1})");//2桁.1桁（小数点以下の入力があるとき）
    regex W4(R"(\d{2})");      //2桁（小数点以下の入力がないとき）


    //文字列の形式を確認
    //上記の4種の形式のどれかに当てはまれば、性別入力へ
    if (regex_match(TAIJU, W1) || regex_match(TAIJU, W2) || regex_match(TAIJU, W3) || regex_match(TAIJU, W4))
        goto GenderZone;

    //当てはまらなければ再度入力（体重入力やり直し）
    else cout << "不正な入力です。再度入力しなおしてください。\n\n";
    goto WeightZone;



GenderZone:

    //性別の入力
    cout << "性別を教えてください。男性なら「m」、女性なら「w」を入力して、Enterキーを押してください。\n";
    cin >> SEIBETSU;

    //「m」か「w」が入力されたらファイル入力へ
    if (SEIBETSU == "m" || SEIBETSU == "w") goto OutfileZone;


    //「m」か「w」以外が入力されたら再度入力
    else cout << "不正な入力です。再度選択してください。\n\n";
    goto GenderZone;



OutfileZone:

    //順番にファイル入力
    outfile << NAMAE << " " << SHINCHO << " " << TAIJU << " " << SEIBETSU << endl;



JudgeZone:

    //続けて入力するかの選択
    cout << "次の人も続けて入力しますか？入力するなら「１」、入力しないなら「２」を入力して、Enterキーを押してください。\n";
    string judge;
    cin >> judge;


    //「1」が入力されたら名前入力ゾーンへ
    if (judge == "1") { cout << "\n次の方の入力を始めてください。\n";goto NameZone; }

    //「2」が入力されたらendへ
    else if (judge == "2")goto end;

    //「1」と「2」以外が入力されたら再度入力
    else cout << "不正な入力です。再度選択してください。\n\n";
    goto JudgeZone;


end:
    cout << "ーーーーー診断結果は以下になります。ーーーーーーーーー---------------" << endl;


}

//男性用BMI関数の宣言
void manBMI(double weight, double height) {

    double mbmi;

    //男性用BMI関数の定義
    mbmi = weight / ((height * 0.01) * (height * 0.01));


    cout << "あなたのBMIは";

    //小数第一位まで出力
    printf("%.1f", mbmi);

    cout << "で";

    //BMIの数値によって出力を変更
    if (mbmi < 17)cout << "痩せすぎです。\nガリガリはモテません！体にもよくないので、ごはんをもりもり食べましょう！";
    else if (17 <= mbmi && mbmi < 18.5)cout << "痩せ気味です。\nごはんをたくさん食べて、筋トレして素敵な身体を手に入れよう！\n";
    else if (18.5 <= mbmi && mbmi < 25)cout << "普通体重です。\n健康的な体重です！この調子で維持しましょう！\n";
    else if (25 <= mbmi && mbmi < 30)cout << "太り気味です。（肥満度１）\n筋肉質の人ならいい感じです！そうではない方はぽっちゃりさん！生活習慣を見直して、健康的な体を目指しましょう！\n";
    else if (30 <= mbmi && mbmi < 35)cout << "太っています。（肥満度２）\nおなかのお肉が、、、。適度な運動を取り入れて、健康的な体を目指しましょう！\n";
    else if (35 <= mbmi && mbmi < 40)cout << "太りすぎです。（肥満度３）\n太りすぎは危険です。このままだと横綱のような貫禄が出てきますよ！食べ過ぎ、運動不足に気を付けましょう！\n";
    else if (mbmi >= 40)cout << "かなり太りすぎです。（肥満度４）\n太りすぎは身体に悪いです。過度な食事は控えましょう！\n";

    cout << endl;
}

//女性用BMI関数の宣言
void womanBMI(double weight, double height) {

    double wbmi;

    //女性用BMI関数の定義
    wbmi = weight / ((height * 0.01) * (height * 0.01));


    cout << "あなたのBMIは";

    //小数第一位まで出力
    printf("%.1f", wbmi);

    cout << "で";

    //BMIの数値によって出力を変更
    if (wbmi < 17)cout << "痩せすぎです。\nこれはモデル体重ですが、痩せすぎは危険なので、ごはんをもりもり食べましょう！";
    else if (17 <= wbmi && wbmi < 18.5)cout << "痩せ気味です。\nプリンセス体重ですが、無理なダイエットはせず、ごはんをたくさん食べましょう！\n";
    else if (18.5 <= wbmi && wbmi < 25)cout << "普通体重です。\n健康的な体重です！この調子で維持しましょう！\n";
    else if (25 <= wbmi && wbmi < 30)cout << "太り気味です。（肥満度１）\nマシュマロボディになっています！生活習慣を見直して、健康的な体を目指しましょう！\n";
    else if (30 <= wbmi && wbmi < 35)cout << "太っています。（肥満度２）\nいわゆるぽっちゃりです！適度な運動を取り入れて、健康的な体を目指しましょう！\n";
    else if (35 <= wbmi && wbmi < 40)cout << "太りすぎです。（肥満度３）\nふくよかボディです！このままでは貫禄が出てしまうので、食べ過ぎ、運動不足に気を付けましょう！\n";
    else if (wbmi >= 40)cout << "かなり太りすぎです。（肥満度４）\n太りすぎは身体に危険があります。過度な食事は控えましょう！\n";

    cout << endl;
}


//ファイルを読み込む関数の定義
void ReadFromFile(string FileName)
{
    //クラスPersonのデータを格納するVectorの宣言
    vector<Person>vbody;

    //ifstreamオブジェクトの構築
    ifstream infile(FileName);

    //Vectorの番号付け
    int n = 0;

    //Vebtorに分割して格納するための宣言
    string Name;  //名前
    double Height;//身長
    double Weight;//体重
    string Gender;//性別

    //順番に読み込む
    while (infile >> Name >> Height >> Weight >> Gender) {

        //要素の追加
        vbody.emplace_back();

        //順番にVectorに格納
        vbody[n].setName(Name);
        vbody[n].setHeight(Height);
        vbody[n].setWeight(Weight);
        vbody[n].setGender(Gender);
        n++;
    }

    //Vevtorに格納されている名前、身長、体重を順番に出力
    size_t s = vbody.size();
    for (size_t i = 0;i < s;++i) {
        cout << vbody[i].getName() << "さん\n" << "身長：" << vbody[i].getHeight() << "cm , 体重："
            << vbody[i].getWeight() << "kg , ";

        //性別が格納されたVectorの要素が男性（「ｍ」と入力されている）だったら、男性用BMI関数に身長と体重を代入する。
        if (vbody[i].getGender() == "m") { cout << "性別：男性" << endl;manBMI(vbody[i].getWeight(), vbody[i].getHeight()); }
        //性別が格納されたVectorの要素が女性（「w」と入力されている）だったら、女性用BMI関数に身長と体重を代入する。
        else if (vbody[i].getGender() == "w") { cout << "性別：女性" << endl; womanBMI(vbody[i].getWeight(), vbody[i].getHeight()); };

    }
}

int main() {

    //文字列の宣言
    string NAME;
    string HEIGHT;
    string WEIGHT;
    string GENDER;

    //文字列を入力する関数
    InputFile(NAME, HEIGHT, WEIGHT, GENDER);

    //"Body.txt"ファイルの読み込み
    ReadFromFile("Body.txt");

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
