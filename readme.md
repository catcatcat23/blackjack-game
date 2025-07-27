# 🎮 Blackjack 21 点游戏 - C++ 实现教程

## 📌 项目简介

这是一个使用 C++ 编写的简化版 Blackjack（黑杰克）托弗牌游戏。玩家和庄家轮流抽牌，目标是尽可能接近 21 分而不爆牌。玩家初始有 \$100 余额，可以下注、抽牌、停牌，直到赢得筹码或输光为止。

---

## 📁 文件结构

```
📁 blackjack_game/
├── blackjack.cpp      // 游戏源码
├── README.md          // 当前教程文档
```

---

## 🔧 编译与运行方式

### ✅ 使用 g++ 编译（推荐）

```bash
g++ -o blackjack blackjack.cpp
./blackjack
```

### ✅ 使用 VSCode / CLion 等 IDE

* 创建新项目
* 将 `blackjack.cpp` 文件复制进去
* 点击运行即可

---

## 🧐 游戏环流说明

### 🌺 牌值说明

| 牌面    | 值                |
| ----- | ---------------- |
| A     | 1 或 11（根据情况自动判断） |
| 2-10  | 本身的数字值           |
| J/Q/K | 10               |

### 👤 玩家行为

* 玩家起始余额为 \$100
* 每轮下注金额不能超过余额
* 玩家起手获得两张牌，可选择：

  * `h`: 抽牌（Hit）
  * `s`: 停止抽牌（Stand）
* 点数超过 21 即爆牌（Busted）

### 🃟 庄家行为

* 起手两张牌（隐藏一张）
* 点数 < 17 必须继续抽牌
* 点数 >= 17 停止抽牌

### 🏆 胜负规则

| 情况        | 结果   |
| --------- | ---- |
| 玩家爆了      | 玩家输  |
| 庄家爆了      | 玩家赢  |
| 玩家点数 > 庄家 | 玩家赢  |
| 玩家点数 < 庄家 | 玩家输  |
| 平局        | 不输不赢 |

---

## 💡 示例演示

### 🎲 示例 1：正常胜利

```
Your balance: $100
Place your bet: 20
Your cards: [10♦][8♣] → Total: 18
Dealer shows: [6♠][??]
Hit or Stand (h/s)? s
Dealer draws: [4♦] → Total: 17
You win!
Your balance is now: $120
```

### 🎲 示例 2：爆牌

```
Your balance: $120
Place your bet: 30
Your cards: [A♠][9♣] → Total: 20
Hit or Stand (h/s)? h
You drew: [5♥]
Your cards: [A♠][9♣][5♥] → Total: 25
You busted!
Your balance is now: $90
```

### 🎲 示例 3：A 自动变成 1

```
Your cards: [A♠][9♣][A♦] → Total: 21
Dealer shows: [9♠][??]
Dealer draws: [8♦] → Total: 24
You win!
Your balance is now: $120
```

### 🎲 示例 4：平局

```
Your cards: [10♣][9♦] → Total: 19
Dealer cards: [8♠][9♥] → Total: 17
Dealer draws: [2♣] → Total: 19
It's a tie.
Your balance is now: $120
```

### 🎲 示例 5：庄家爆牌

```
Your cards: [7♠][9♥] → Total: 16
Dealer cards: [4♦][9♠] → Total: 13
Dealer draws: [10♥] → Total: 23
You win!
Your balance is now: $150
```

---

## 📆 代码文件结构说明

### 🔹 `Card` 类

```cpp
class Card {
    string rank, suit;
    int value;  // A=11, JQK=10
};
```

### 🔹 `Deck` 类

```cpp
class Deck {
    vector<Card> cards;
    void shuffle();  // 随机洗牌
    Card deal();     // 发一张牌
};
```

### 🔹 `Player` 类

```cpp
class Player {
    vector<Card> hand;
    int balance;  // 仅对玩家有效
    int getScore();       // 自动处理 A=1/11
    void showHand();
};
```

### 🔹 游戏逻辑主循环

```cpp
while (player.balance > 0) {
    // 输入下注
    // 发牌，展示手牌
    // 玩家 hit/stand
    // 庄家抽牌策略
    // 判断胜负，更新余额
    // 是否继续下一局
}
```


## 🔋 main() 函数：游戏流程详解

```cpp
while (player.balance > 0) {
    // 1. 重置手牌
    // 2. 输入下注
    // 3. 发牌，玩家和庄家各 2 张
    // 4. 显示玩家手牌，隐藏庄家一张
    // 5. 玩家选择 hit/stand，爆牌结束
    // 6. 庄家手牌全部显示，<17 继续抽
    // 7. 比分，判定胜负
    // 8. 更新玩家余额
    // 9. 判断是否输光，是否继续下一局
    // 10. 剩余牌不足时重新洗牌
}
```

### 🔹 实际代码详解：

1. **初始化牌堆和玩家庄家对象**

```cpp
Deck deck;
Player player("You"), dealer("Dealer");
```

2. **如果玩家余额 > 0，初始化手牌，进入游戏循环**

```cpp
while (player.balance > 0) {
    player.resetHand();
    dealer.resetHand();
```

3. **输入下注，根据玩家余额进行校验**

```cpp
int bet;
cout << "\nYour balance: $" << player.balance << endl;
cout << "Place your bet: ";
while (!(cin >> bet) || bet <= 0 || bet > player.balance) {
    cin.clear(); cin.ignore(999, '\n');
    cout << "Invalid bet. Enter again: ";
}
```

4. **每人发两张牌**

```cpp
player.addCard(deck.deal());
player.addCard(deck.deal());
dealer.addCard(deck.deal());
dealer.addCard(deck.deal());
```

5. **显示玩家全部牌，庄家显示1张（隐藏一张）**

```cpp
cout << "\nYour cards: "; player.showHand();
cout << "Dealer shows: "; dealer.showHand(false);
```

6. **玩家选择 Hit 或 Stand**

```cpp
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
```

7. **玩家分数 > 21，爆牌结束；否则庄家回合**

```cpp
if (player.getScore() > 21) {
    cout << "You busted!\n";
    player.balance -= bet;
} else {
    // Dealer plays...
```

8. **庄家比玩家操作简单：<17 继续抽，否则停**

```cpp
while (dealer.getScore() < 17) {
    dealer.addCard(deck.deal());
    cout << "Dealer draws: "; dealer.hand.back().display(); cout << endl;
}
```

9. **比较分数，判定胜负，更新余额**

```cpp
if (dScore > 21 || pScore > dScore) {
    cout << "You win!\n";
    player.balance += bet;
} else if (pScore < dScore) {
    cout << "You lose!\n";
    player.balance -= bet;
} else {
    cout << "It's a tie.\n";
}
```

10. **判断是否继续游戏**

```cpp
cout << "Play again? (y/n): ";
cin >> choice;
if (choice != "y") break;
```

11. **剩余牌太少，重新生成牌堆**

```cpp
if (deck.cards.size() < 15) {
    cout << "\n🔄 Reshuffling deck...\n";
    deck = Deck();
}
```

---


## 🧪 测试建议

* ✅ 输入非法下注金额（如负数、非数字）
* ✅ 玩家点数为 21（Blackjack）
* ✅ 多个 A 自动变成 1
* ✅ 庄家爆牌场景

---

## 📝 注意事项

* 所有 A 默认记为 11，若总分超 21 会自动将 A 减为 1
* 玩家爆牌立即结束该局
* 剩余牌 < 15 时自动重新洗牌

---

## 📢 结言

本项目适合 C++ 面向对象编程入门者练习。建议在掌握本项目后尝试：

* 多人游戏支持
* 图形界面（如 Qt）
* 账户系统、排行榜等扩展功能



Happy Coding 🧑‍💻
