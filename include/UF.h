class UF
{
    public:
        explicit UF(int n): count(n)
        {
            id = new int[n];
            for(int i = 0; i < n; i++)
            {
                id[i] = i;
            }
        }

        virtual void join(int p, int q) = 0;
        virtual int find(int p) = 0;
        virtual bool is_connected(int p, int q)
        {
            return find(p) == find(q);
        }
         int get_count()
        {
            return count;
        }
        ~UF()
        {
            delete [] id;
        }
    protected:
        int* id;
        int count;

};

class QuickFindUF : public UF
{
    public:
        QuickFindUF(int n): UF(n) 
        {}
        void join(int p, int q) override
        {
            int pID = find(p);
            int qID = find(q);

            if(pID == qID) return;

            for(int i = 0; i < count; i++)
            {
                if(id[i] == pID)
                {
                    id[i] = qID;
                }
            }
            count--;
        }
        int find(int p) override
        {
            return id[p];
        }
};

class QuickJoinUF : public UF
{
    public:
        QuickJoinUF(int n): UF(n) 
        {}

        void join(int p, int q) override
        {
            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot) return;

            id[pRoot] = qRoot;
            count--;
        }

        int find(int p) override
        {
            while(p != id[p]) p = id[p];
            return p;
        }

};

class WeightedQuickJoinUF : public QuickJoinUF
{
    public:
        WeightedQuickJoinUF(int n): QuickJoinUF(n)
        {
            size = new int[n];
            for(int i = 0; i < n; i++)
            {
                size[i] = 1;
            }
        }

        void join(int p, int q) override
        {
            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot) return;

            if(size[pRoot] > size[qRoot])
            {
                id[qRoot] = pRoot;
                size[qRoot] += size[pRoot];
            }
            else
            {
                id[pRoot] = qRoot;
                size[pRoot] += size[qRoot];
            }
            count--;
        }
    protected:
        int* size;
};

