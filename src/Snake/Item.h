#pragma once

#include "Snake.h"

namespace GZ {
    /// <summary>
    /// An flag enumerate of all items.
    /// </summary>
    /// 
    /// Addition infomation about flag enumerate:
    /// 
    /// You can use 
    ///     unsigned int flag = ItemType::PORTAL | ItemType::GOLD;
    ///     (flag = 0b00000011)
    /// to represent the portal and the golden apple together.
    /// and use:
    ///     flag & ItemType::PORTAL;
    ///     (flag & ItemType::PORTAL == 0b00000001) == true
    ///     (flag & ItemType::CUT    == 0b00000000) == false
    /// to get whether the flag has ItemType::PORTAL.
    /// 
    enum class ItemType: unsigned int {
        NONE   = 0x00000000,
        PORTAL = 0x00000001, // 0b00000001
        GOLD   = 0x00000002, // 0b00000010
        CUT    = 0x00000004, // 0b00000100
        ALL    = 0xffffffff,
    };

    /// <summary>
    /// The base class for all items.
    /// </summary>
    class Item
    {
    public:
        Item(Pos p,int s) : pos(p), score(s) {};
        Pos pos;
        int score;

        /// <summary>
        /// This method will be called when the snake get the item.
        /// </summary>
        /// <param name="snake">snake object</param>
        virtual void Get(Snake* snake) = 0;

        /// <summary>
        /// Show the item on the game area.
        /// </summary>
        virtual void Show() = 0;

        /// <summary>
        /// Get the type for current item.
        /// </summary>
        /// <returns></returns>
        virtual ItemType GetType() = 0;
    };

    /// <summary>
    /// The portal item.
    /// <para>Teleport your snake to a random position.</para>
    /// </summary>
    class Portal : public Item {
    private:
        bool Detect(Pos pos, Snake* snake);

    public:
        Portal(Pos p): Item(p, 20) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();

        /// <summary>
        /// Determine whether to generate the item with specific generation probability.
        /// </summary>
        static bool TryGen();
    };

    /// <summary>
    /// The Golden Apple item.
    /// <para>Lengthen your snake with 5 blocks.</para>
    /// </summary>
    class Gold : public Item {
    public:
        Gold(Pos p) : Item(p, 100) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();

        /// <summary>
        /// Determine whether to generate the item with specific generation probability.
        /// </summary>
        static bool TryGen();
    };

    /// <summary>
    /// The Cut item.
    /// <para>Shorten your snake with 5 blocks but keep your score.</para>
    /// </summary>
    class Cut : public Item {
    public:
        Cut(Pos p) : Item(p, 50) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();

        /// <summary>
        /// Determine whether to generate the item with specific generation probability.
        /// </summary>
        static bool TryGen();
    };
}


