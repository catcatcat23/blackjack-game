#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

// ------------------- Card 类 -------------------
class Card {
public:
    string suit;  // 花色
    string rank;  // 点数
    int value;

    Card(string r, string s) : rank(r), suit(s) {
        if (r == "A") value = 11;
        else if (r == "K" || r == "Q" || r == "J") value = 10;
        else value = std::atoi(r.c_str());
    }

    void display() const {
        cout << "[" << rank << suit << "] ";
    }
};

// ------------------- Deck 类 -------------------
class Deck {
public:
    vector<Card> cards;

    Deck() {
        string suits[] = {"♠", "♥", "♦", "♣"};
        string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        for (string s : suits)
            for (string r : ranks)
                cards.emplace_back(r, s);
        shuffle();
    }

    void shuffle() {
        srand(time(0));
        for (int i = 0; i < cards.size(); ++i) {
            int j = rand() % cards.size();
            swap(cards[i], cards[j]);
        }
    }


    Card deal() {
        Card top = cards.back();
        cards.pop_back();
        return top;
    }
};

// ------------------- Player 类 -------------------
class Player {
public:
    vector<Card> hand;
    int balance;
    string name;

    Player(string n, int b = 100) : name(n), balance(b) {}

    void addCard(Card c) {
        hand.push_back(c);
    }

    int getScore() {
        int score = 0, aces = 0;
        for (Card c : hand) {
            score += c.value;
            if (c.rank == "A") aces++;
        }
        while (score > 21 && aces > 0) {
            score -= 10;  // A = 1 而不是 11
            aces--;
        }
        return score;
    }

    void showHand(bool showAll = true) {
        for (size_t i = 0; i < hand.size(); i++) {
            if (!showAll && i == 1) {
                cout << "[??] ";  // 隐藏第二张牌
            } else {
                hand[i].display();  // 显示牌面
            }
        }

    // 只在所有牌都展示时显示总分
    if (showAll) {
        cout << " → Total: " << getScore() << endl;
    } else {
        cout << endl;  // 如果不显示总分，直接换行
    }
}
    void resetHand() {
        hand.clear();
    }
};

// ------------------- 游戏主流程 -------------------
int main() {
    Deck deck;
    Player player("You"), dealer("Dealer");
    string choice;

    cout << "🎮 Welcome to Blackjack!" << endl;
    while (player.balance > 0) {
        player.resetHand();
        dealer.resetHand();

        int bet;
        cout << "\nYour balance: $" << player.balance << endl;
        cout << "Place your bet: ";
        while (!(cin >> bet) || bet <= 0 || bet > player.balance) {
            cin.clear(); cin.ignore(999, '\n');
            cout << "Invalid bet. Enter again: ";
        }

        player.addCard(deck.deal());
        player.addCard(deck.deal());
        dealer.addCard(deck.deal());
        dealer.addCard(deck.deal());

        cout << "\nYour cards: "; player.showHand();
        cout << "Dealer shows: "; dealer.showHand(false);

        while (player.getScore() < 21) {
            cout << "Hit or Stand (h/s)? ";
            cin >> choice;
            if (choice == "h") {
                player.addCard(deck.deal());
                cout << "You drew: "; player.hand.back().display(); cout << endl;
                cout << "Your cards: "; player.showHand();
            } else if (choice == "s") break;
            else cout << "Invalid input. Type 'h' or 's'.\n";
        }

        int pScore = player.getScore();
        if (pScore > 21) {
            cout << "You busted!\n";
            player.balance -= bet;
        } else {
            cout << "\nDealer's turn...\n";
            cout << "Dealer's cards: "; dealer.showHand();
            while (dealer.getScore() < 17) {
                dealer.addCard(deck.deal());
                cout << "Dealer draws: "; dealer.hand.back().display(); cout << endl;
            }

            int dScore = dealer.getScore();
            cout << "Dealer's total: " << dScore << endl;

            if (dScore > 21 || pScore > dScore) {
                cout << "You win!\n";
                player.balance += bet;
            } else if (pScore < dScore) {
                cout << "You lose!\n";
                player.balance -= bet;
            } else {
                cout << "It's a tie.\n";
            }
        }

        if (player.balance == 0) {
            cout << "\nGame over! You're out of money.\n";
            break;
        }

        cout << "Play again? (y/n): ";
        cin >> choice;
        if (choice != "y") break;

        if (deck.cards.size() < 15) {
            cout << "\n🔄 Reshuffling deck...\n";
            deck = Deck();
        }
    }

    cout << "\nThanks for playing! Final balance: $" << player.balance << endl;
    return 0;
}
