using System;
using System.Collections.Generic;
using System.Text;

namespace ParamSet
{
    public class QueueManager<T>
    {
        private Queue<T> queue = new Queue<T>();

        
        public  void Add(T t)
        {
            queue.Enqueue(t);
        }

        public T Get()
        {
            return queue.Dequeue();
        }

        public bool IsGet(T t)
        {
            bool resule = false;
            resule = queue.Contains(t);
            return resule;
        }

        public bool IsHaveElement()
        {
            if (queue.Count <= 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        public int GetQueueCount()
        {
            return queue.Count;
        }
    }
}
