template <typename T>
Queue<T>::Queue() : index(0), sz(0), data(nullptr) {}

template <typename T>
Queue<T>::Queue(const Queue<T> &tmp) : index(tmp.index), sz(tmp.sz) {
  data = new T[sz];
  for (int i = 0; i < index; i++) data[i] = tmp.data[i];
}

template <typename T>
void Queue<T>::pop() {
  if (!index) index--;
}

template <typename T>
void Queue<T>::push(const T &x) {
  if (index == sz) {
    int nsz = (sz == 0) ? 1 : sz * 2;
    T *ndata = new T[nsz];
    for (int i = 0; i < index; i++) {
      ndata[i] = data[i];
    }
    delete[] data;
    sz = nsz;
    data = ndata;
  }

  data[index++] = x;
}

template <typename T>
int Queue<T>::size() {
  return index;
}

template <typename T>
T Queue<T>::front() {
  if (index)
    return data[index - 1];
  else
    throw std::runtime_error("Queue is empty");
}

template <typename T>
T Queue<T>::back() {
  if (index)
    return data[0];
  else
    throw std::runtime_error("Queue is empty");
}

template <typename T>
bool Queue<T>::empty() {
  return !index;
}

template <typename T>
Queue<T>::~Queue() {
  delete[] data;
}