template <typename T>
class MaxPQ
{
    public:
        MaxPQ(int maxN)
        {
            pq = new T[maxN + 1];
        }
        ~MaxPQ()
        {
            delete [] pq;
        }
        void insert(const T& v)
        {
            pq[++N] = v;
            swim(N);
        }
        T delMax()
        {
            T max = pq[1];
            exch(1, N--);
            sink(1);
            return max;
        }
        bool is_empty()
        {
            return N == 0;
        }
        int get_size()
        {
            return N;
        }
    private:
        T* pq;
        int N = 0;
        void exch(int i, int j)
        {
            T t = pq[i]; pq[i] = pq[j]; pq[j] = t;
        }
        void swim(int k)
        {
            while(k > 1 && (pq[k/2] < pq[k]))
            {
                exch(k/2, k);
                k = k/2;
            }
        }

        void sink(int k)
        {
            while(2*k <= N)
            {
                int j = 2*k;
                if(j < N && (pq[j] < pq[j+1])) 
                    j++;
                if(!(pq[k] < pq[j])) 
                    break;
                exch(k, j);
                k = j;
            }
        }
};

template <typename T>
class IndexMaxPQ
{
    public:
        IndexMaxPQ(int maxN)
        {
            keys = new T[maxN];
            pq = new int[maxN + 1];
            qp = new int[maxN];

            for(int i = 0; i < maxN; i++)
            {
                qp[i] = -1;
            }
        }
        ~IndexMaxPQ()
        {
            delete [] keys;
            delete [] pq;
            delete [] qp;
        }

        bool contains(int k) {
            return qp[k] != -1;
        }
        void insert(int k, const T& v)
        {
            N++;
            keys[k] = v;
            pq[N] = k;
            qp[k] = N - 1;
            swim(N);
        }
        void change_key(int k, const T& v)
        {
            int index = qp[k];
            keys[k] = v;
            swim(index);
            sink(index);
        }

        void delete_key(int k)
        {
            int index = qp[k];
            exch(index, N--);
            qp[k] = -1;
            swim(index);
            sink(index);
        }

        T& max()
        {
            T& max = keys[pq[1]];
            return max;
        }

        int min_index()
        {
            return pq[1];
        }

        T& del_max()
        {
            T& max = keys[pq[1]];
            exch(1, N--);
            qp[pq(N + 1)] = -1;
            sink(1);

            return max;
        }

        bool is_empty()
        {
            return N == 0;
        }
        int get_size()
        {
            return N;
        }
    private:
        T* keys;
        int* pq;
        int* qp;
        int N = 0;
        void exch(int i, int j)
        {
            int t = pq[i]; pq[i] = pq[j]; pq[j] = t;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }
        void swim(int k)
        {
            while(k > 1 && (keys[pq[k/2]] < keys[pq[k]]))
            {
                exch(k/2, k);
                k = k/2;
            }
        }

        void sink(int k)
        {
            while(2*k <= N)
            {
                int j = 2*k;
                if(j < N && (keys[pq[j]] < keys[pq[j+1]])) 
                    j++;
                if(!(keys[pq[k]] < keys[pq[j]])) 
                    break;
                exch(k, j);
                k = j;
            }
        }
};

template <typename T>
class MinPQ
{
    public:
        MinPQ(int maxN)
        {
            pq = new T[maxN + 1];
        }
        ~MinPQ()
        {
            delete [] pq;
        }
        void insert(const T& v)
        {
            pq[++N] = v;
            swim(N);
        }
        T delMin()
        {
            T max = pq[1];
            exch(1, N--);
            sink(1);
            return max;
        }
        bool is_empty()
        {
            return N == 0;
        }
        int get_size()
        {
            return N;
        }
    private:
        T* pq;
        int N = 0;
        void exch(int i, int j)
        {
            T t = pq[i]; pq[i] = pq[j]; pq[j] = t;
        }
        void swim(int k)
        {
            while(k > 1 && (pq[k] < pq[k/2]))
            {
                exch(k/2, k);
                k = k/2;
            }
        }

        void sink(int k)
        {
            while(2*k <= N)
            {
                int j = 2*k;
                if(j < N && (pq[j+1] < pq[j])) 
                    j++;
                if(!(pq[j] < pq[k])) 
                    break;
                exch(k, j);
                k = j;
            }
        }
};

template <typename T>
class IndexMinPQ
{
    public:
        IndexMinPQ(int maxN)
        {
            keys = new T[maxN];
            pq = new int[maxN + 1];
            qp = new int[maxN];

            for(int i = 0; i < maxN; i++)
            {
                qp[i] = -1;
            }
        }
        ~IndexMinPQ()
        {
            delete [] keys;
            delete [] pq;
            delete [] qp;
        }

        bool contains(int k) {
            return qp[k] != -1;
        }
        void insert(int k, const T& v)
        {
            N++;
            keys[k] = v;
            pq[N] = k;
            qp[k] = N - 1;
            swim(N);
        }
        void change_key(int k, const T& v)
        {
            int index = qp[k];
            keys[k] = v;
            swim(index);
            sink(index);
        }

        void delete_key(int k)
        {
            int index = qp[k];
            exch(index, N--);
            qp[k] = -1;
            swim(index);
            sink(index);
        }

        T& min()
        {
            T& min = keys[pq[1]];
            return min;
        }

        int max_index()
        {
            return pq[1];
        }

        T& del_min()
        {
            T& min = keys[pq[1]];
            exch(1, N--);
            qp[pq(N + 1)] = -1;
            sink(1);

            return min;
        }

        bool is_empty()
        {
            return N == 0;
        }
        int get_size()
        {
            return N;
        }
    private:
        T* keys;
        int* pq;
        int* qp;
        int N = 0;
        void exch(int i, int j)
        {
            int t = pq[i]; pq[i] = pq[j]; pq[j] = t;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }
        void swim(int k)
        {
            while(k > 1 && (keys[pq[k]] < keys[pq[k/2]]))
            {
                exch(k/2, k);
                k = k/2;
            }
        }

        void sink(int k)
        {
            while(2*k <= N)
            {
                int j = 2*k;
                if(j < N && (keys[pq[j + 1]] < keys[pq[j]])) 
                    j++;
                if(!(keys[pq[j]] < keys[pq[k]])) 
                    break;
                exch(k, j);
                k = j;
            }
        }
};
