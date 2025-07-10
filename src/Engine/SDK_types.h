#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace Unity {
    template <typename T>
    struct monoArray
    {
        void* klass;
        void* monitor;
        void* bounds;
        int   max_length;
        T vector[65535];

        T& operator [] (int i)
        {
            return vector[i];
        }

        const T& operator [] (int i) const
        {
            return vector[i];
        }

        bool Contains(T item)
        {
            for (int i = 0; i < max_length; i++)
            {
                if (vector[i] == item) return true;
            }
            return false;
        }
    };

    template<typename T>
    struct monoList {
        void* unk0;
        void* unk1;
        monoArray<T>* items;
        int size;
        int version;

        T getItems() {
            return items->getPointer();
        }

        int getSize() {
            return size;
        }

        int getVersion() {
            return version;
        }
    };

    struct MonoArray {
        void* object1;
        void* object2;
        int32_t length;
        uint16_t chars[32];
    };

    template<typename T>
    using Array = monoArray<T>;

    template<typename TKey, typename TValue>
    struct Dictionary
    {
        struct KeysCollection;
        struct ValueCollection;

        struct Entry1
        {
            int hashCode;
            int next;
            TKey key;
            void* valu;
        };

        void* kass;
        void* monitor;
        Array<int>* buckets;
        Array<Entry1>* entries;
        int count;
        int version;
        int freeList;
        int freeCount;
        void* comparer;
        KeysCollection* keys;
        ValueCollection* values;
        void* _syncRoot;

        void* get_Comparer()
        {
            return comparer;
        }

        int get_Count()
        {
            return count;
        }

        KeysCollection get_Keys()
        {
            if (!keys) keys = new KeysCollection(this);
            return (*keys);
        }

        ValueCollection get_Values()
        {
            if (!values) values = new ValueCollection(this);
            return (*values);
        }

        TValue operator [] (TKey key)
        {
            int i = FindEntry(key);
            if (i >= 0) return void* ((*entries)[i].valu);
            return TValue();
        }

        const TValue operator [] (TKey key) const
        {
            int i = FindEntry(key);
            if (i >= 0) return (*entries)[i].valu;
            return TValue();
        }

        int FindEntry(TKey key)
        {
            for (int i = 0; i < count; i++)
            {
                if ((*entries)[i].key == key) return i;
            }
            return -1;
        }

        bool ContainsKey(TKey key)
        {
            return FindEntry(key) >= 0;
        }

        bool ContainsValue(TValue value)
        {
            for (int i = 0; i < count; i++)
            {
                if ((*entries)[i].hashCode >= 0 &&
                    (*entries)[i].valu == value) return true;
            }
            return false;
        }

        bool TryGetValue(TKey key, TValue* value)
        {
            int i = FindEntry(key);
            if (i >= 0) {
                *value = (*entries)[i].valu;
                return true;
            }
            *value = TValue();
            return false;
        }

        TValue GetValueOrDefault(TKey key)
        {
            int i = FindEntry(key);
            if (i >= 0) {
                return (*entries)[i].valu;
            }
            return TValue();
        }

        struct KeysCollection
        {
            Dictionary* dictionary;

            KeysCollection(Dictionary* dictionary)
            {
                this->dictionary = dictionary;
            }

            TKey operator [] (int i)
            {
                auto entries = dictionary->entries;
                if (!entries) return TKey();
                return (*entries)[i].key;
            }

            const TKey operator [] (int i) const
            {
                auto entries = dictionary->entries;
                if (!entries) return TKey();
                return (*entries)[i].key;
            }

            int get_Count()
            {
                return dictionary->get_Count();
            }
        };

        struct ValueCollection
        {
            Dictionary* dictionary;

            ValueCollection(Dictionary* dictionary)
            {
                this->dictionary = dictionary;
            }

            TValue operator [] (int i)
            {
                auto entries = dictionary->entries;
                if (!entries) return TValue();
                return (*entries)[i].valu;
            }

            const TValue operator [] (int i) const
            {
                auto entries = dictionary->entries;
                if (!entries) return TValue();
                return (*entries)[i].valu;
            }

            int get_Count()
            {
                return dictionary->get_Count();
            }
        };
    };

    struct String {
        static String* FromCString(std::string text);
        std::string ToCString();
    };

    // sqrt(
    // (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2
    // )
    struct Vector3 {
        float x = 0, y = 0, z = 0;
        float distance(Vector3 b) { 
            return sqrt(
                pow(x - b.x, 2) + pow(y - b.y, 2) + pow(z - b.z, 2)
            ); 
        }
        bool zero() { return (x == 0 && y == 0 && z == 0); }
        Vector3 operator *(float k) { return { x * k, y * k, z * k }; }
        Vector3 operator -(Vector3 B) { return { x - B.x, y - B.y, z - B.z }; }
        Vector3 operator +(Vector3 B) { return { x + B.x, y + B.y, z + B.z }; }
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3() {}

        static Vector3 Null() {
            return { 0, 0, 0 };
        }
    };

    class Transform {
    public:
        Vector3 getPosition();
        void setPosition(Vector3 pos);
    };

    struct Component {};

    struct Object {};

    struct GameObject {
        std::string Name();
        void* GetComponent(const char* name);

        Transform* GetTransform();
    };

    struct Vector2 {
        float x, y;
    };

    enum CursorLockMode {
        None = 0,
        Lock = 1,
        Confined = 2
    };

    struct Cursor {
        static void set_visible(bool value);
        static bool get_visible();
        static void set_lockState(CursorLockMode target);
    };

    struct Bounds {
        Vector3 center;
        Vector3 extent;
    };

    struct Text {
        void set_text(String* text);
    };

    struct Camera {
        void set_fieldOfView(float value);
    };

    struct Time {
        static void set_timeScale(float value);
    };
}

namespace MoleMole {
    enum EntityType : int32_t {
        None = 0,
        Avatar = 1,
        Monster = 2,
        Bullet = 3,
        AttackPhyisicalUnit = 4, 
        AOE = 5, 
        Camera = 6, 
        EnviroArea = 7, 
        Equip = 8, 
        MonsterEquip = 9,
        Grass = 10, 
        Level = 11, 
        NPC = 12, 
        TransPointFirst = 13,
        TransPointFirstGadget = 14,
        TransPointSecond = 15, 
        TransPointSecondGadget = 16, 
        DropItem = 17, 
        Field = 18, 
        Gadget = 19, 
        Water = 20, 
        GatherPoint = 21, 
        GatherObject = 22, 
        AirflowField = 23,
        SpeedupField = 24,
        Gear = 25,
        Chest = 26,
        EnergyBall = 27,
        ElemCrystal = 28,
        Timeline = 29,
        Worktop = 30,
        Team = 31,
        Platform = 32,
        AmberWind = 33,
        EnvAnimal = 34,
        SealGadget = 35,
        Tree = 36,
        Bush = 37,
        QuestGadget = 38,
        Lightning = 39,
        RewardPoint = 40, 
        RewardStatue = 41, 
        MPLevel = 42, 
        WindSeed = 43,
        MpPlayRewardPoint = 44,
        ViewPoint = 45,
        RemoteAvatar = 46,
        GeneralRewardPoint = 47,
        PlayTeam = 48,
        OfferingGadget = 49,
        EyePoint = 50, 
        MiracleRing = 51, 
        Foundation = 52, 
        WidgetGadget = 53, 
        Vehicle = 54,
        DangerZone = 55,
        EchoShell = 56,
        HomeGatherObject = 57,
        Projector = 58,
        Screen = 59,
        CustomTile = 60,
        FishPool = 61,
        FishRod = 62,
        CustomGadget = 63,
        RoguelikeOperatorGadget = 64,
        ActivityInteractGadget = 65,
        BlackMud = 66,
        SubEquip = 67,
        UIInteractGadget = 68,
        NightCrowGadget = 69,
        Partner = 70,
        DeshretObeliskGadget = 71,
        CoinCollectLevelGadget = 72,
        UgcSpecialGadget = 73,
        UgcTowerLevelUpGadget = 74,
        JourneyGearOperatorGadget = 75,
        CurveMoveGadget = 76
    };

    class BaseEntity {
    public:
        Unity::Vector3 getPosition();
        void setPosition(Unity::Vector3 pos);

        Unity::GameObject* get_GameObject();

        uint32_t runtimeId();
        EntityType type();

        std::string name();

        void* animator();
    };

    class EntityManager {
    public:
        static EntityManager* get_EntityManager();
        std::vector<BaseEntity*> entities();
        BaseEntity* avatar();
    };

    class LoadingManager {
    public:
        static LoadingManager* get_LoadingManager();

        bool IsLoaded();
    };

    struct SceneAvatarInfo {};

    struct SceneEntityInfo {};

    struct ProtoVector {
        char _[0x20];
        float x;
        float y;
        float z;
    };

    struct Rect
    {
        float m_XMin;
        float m_YMin;
        float m_Width;
        float m_Height;
    };

    struct MotionInfo {
        char _[0x20];
        ProtoVector* pos1;
        ProtoVector* pos2;
        ProtoVector* pos3;
        ProtoVector* pos4;
        char __[0x8];
        uint32_t a5;
        uint32_t a6;
        uint32_t a7;
        int32_t state;
        uint32_t ulong;
        uint32_t a9;
    };
}