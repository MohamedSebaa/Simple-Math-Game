
#include <iostream>
using namespace std;

enum enLevelOfQuize { Easy = 1, Med = 2, Hard = 3, MixLevl = 4 };
enum enOperationTypes { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };



struct stQuize
{
    short NumberOfRighesAnswers;
    short NumberOfWrongAnswers;
    enLevelOfQuize LevelOfQuize;
    enOperationTypes OperationType;
    short NumberOfQuestion;
    char OperationTupeChar;
};



int RandomNumber(int From, int To)
{

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short HowManyQuestion()
{
    short NumberOfQuestions;
    do
    {
        cout << "How many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 0);
    return NumberOfQuestions;
}

enOperationTypes AskForOperationType()
{
    short OperationType = 1;
    do
    {
        cout << "Enter Operation Type [1] Add ,[2] Sub ,[3] Mul ,[4] Div ,[5] Mix ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationTypes)OperationType;

}

enLevelOfQuize AskForQuizeLevel()

{
    short QuizeLevel = 1;
    do
    {
        cout << "Enter Questions Level [1] Easy ,[2] Mid ,[3] Hard ,[4] Mix ? ";
        cin >> QuizeLevel;
    } while (QuizeLevel < 1 || QuizeLevel > 4);
    return (enLevelOfQuize)QuizeLevel;

}

void EasyLevelNumbers(short& Number1, short& Number2)
{
    Number1 = RandomNumber(1, 10);
    Number2 = RandomNumber(1, 10);

}

void MedLevelNumbers(short& Number1, short& Number2)
{
    Number1 = RandomNumber(25, 50);
    Number2 = RandomNumber(25, 50);

}

void HardLevelNumbers(short& Number1, short& Number2)
{
    Number1 = RandomNumber(50, 100);
    Number2 = RandomNumber(50, 100);

}

void MixLevelNumbers(short& Number1, short& Number2)
{
    short RandomChoice;
    RandomChoice = RandomNumber(1, 3);
    if (RandomChoice == 1)
        EasyLevelNumbers(Number1, Number2);
    else if (RandomChoice == 2)
        MedLevelNumbers(Number1, Number2);
    else
        HardLevelNumbers(Number1, Number2);
}

short CalulResult(enOperationTypes OperationType, short Number1, short Number2)
{
    if (OperationType == enOperationTypes::Add)
        return Number1 + Number2;
    else if (OperationType == enOperationTypes::Sub)
        return Number1 - Number2;
    else if (OperationType == enOperationTypes::Mul)
        return Number1 * Number2;
    else
        return Number1 / Number2;
}

short ReadResult()
{
    short UserAnswer;
    cin >> UserAnswer;
    return UserAnswer;
}

string ChoiceCharacterName(enOperationTypes OperationType)
{
    string arrGameChoice[5] = { "+","-","x","/","Mix" };
    return arrGameChoice[OperationType - 1];
}

string ChoiceLevelName(enLevelOfQuize LecelOfQuize)
{
    string arrLevelChoice[4] = { "Easy","Med","Hard","Mix" };
    return arrLevelChoice[LecelOfQuize - 1];
}

void IsACorrectAnswer(bool& IsCorrect)
{
    if (IsCorrect)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }


}


string PrintEffectOfRound(bool IsTrueAnswer)
{
    if (IsTrueAnswer == true)
        return "\nRight Answer :-)\n";
    else
        return "\nWrong Answer :-(\n";
}

void PrintQuestion(string OperationTypeChar, short Number1, short Number2)
{
    cout << Number1 << endl;
    cout << Number2 << " " << OperationTypeChar;
    cout << "\n_________________\n";
}

void PrintFinalGameEffect(stQuize Quize)
{
    cout << "\n__________________________________\n\n";
    if (Quize.NumberOfRighesAnswers >= Quize.NumberOfWrongAnswers)
    {
        cout << "  Final Result is PASS :-)";
    }
    else
    {
        cout << "  Final Result is Fail :-(";
    }
    cout << "\n__________________________________\n";
}


stQuize QuizeQuestions(short NumberOfQuestions)
{
    short Number1 = 0, Number2 = 0;
    stQuize Quize;
    enOperationTypes TempOperation = enOperationTypes::Add;
    Quize.NumberOfQuestion = NumberOfQuestions;
    Quize.LevelOfQuize = AskForQuizeLevel();
    Quize.OperationType = AskForOperationType();
    Quize.NumberOfRighesAnswers = 0;
    Quize.NumberOfWrongAnswers = 0;

    for (short QuestionNumber = 1; QuestionNumber <= NumberOfQuestions; QuestionNumber++)
    {
        cout << "\nQuestion [" << QuestionNumber << "/" << NumberOfQuestions << "]" << endl;

        if (Quize.OperationType == enOperationTypes::MixOp)
            TempOperation = (enOperationTypes)RandomNumber(1, 4);
        else
            TempOperation = Quize.OperationType;

        if (Quize.LevelOfQuize == enLevelOfQuize::Easy)
            EasyLevelNumbers(Number1, Number2);
        else if (Quize.LevelOfQuize == enLevelOfQuize::Med)
            MedLevelNumbers(Number1, Number2);
        else if (Quize.LevelOfQuize == enLevelOfQuize::Hard)
            HardLevelNumbers(Number1, Number2);
        else
            MixLevelNumbers(Number1, Number2);

        PrintQuestion(ChoiceCharacterName(TempOperation), Number1, Number2);
        bool IsCorrect = CalulResult(TempOperation, Number1, Number2) == ReadResult();
        cout << PrintEffectOfRound(IsCorrect);
        if (!IsCorrect)
            cout << "The right answer is : " << CalulResult(TempOperation, Number1, Number2) << "\n\n";
        IsACorrectAnswer(IsCorrect);

        if (IsCorrect)
            Quize.NumberOfRighesAnswers++;
        else
            Quize.NumberOfWrongAnswers++;
    }



    return Quize;
}

void PrintResultOfGame(stQuize Quize)
{
    cout << "\nNumber of Questions      : " << Quize.NumberOfQuestion;
    cout << "\nQuestion Level           : " << ChoiceLevelName(Quize.LevelOfQuize);
    cout << "\nOperation Type           : " << ChoiceCharacterName(Quize.OperationType);
    cout << "\nNumber of Right Answers  : " << Quize.NumberOfRighesAnswers;
    cout << "\nNumber of Wrong Answers  : " << Quize.NumberOfWrongAnswers;
    cout << "\n__________________________________\n";

}

void ResetScreen()
{
    system("cls");
    system("color 07");

}

void StartGame()
{
    char PlayAgaine = 'Y';
    do
    {
        ResetScreen();
        stQuize Quize = QuizeQuestions(HowManyQuestion());
        PrintFinalGameEffect(Quize);
        PrintResultOfGame(Quize);
        cout << "\nDo you want to play again ? Y/N ";
        cin >> PlayAgaine;
    } while (PlayAgaine == 'y' || PlayAgaine == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
