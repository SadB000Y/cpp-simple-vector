// вставьте сюда ваш код для класса ArrayPtr
// внесиnте в него изменения, 
// которые позволят реализовать move-семантику
#include <cassert>
#include <cstdlib>
#include <algorithm>
template <typename Type>
class ArrayPtr {
public:
    // Инициализирует ArrayPtr нулевым указателем
    ArrayPtr() = default;
    
    ArrayPtr(ArrayPtr&& other) noexcept 
        : raw_ptr_(std::move(other.raw_ptr_)) {
        other.raw_ptr_ = nullptr;
    }

    // Оператор перемещения
    ArrayPtr& operator=(ArrayPtr&& other) noexcept {
        if (this != &other) {
            delete [] raw_ptr_;
            raw_ptr_ = std::move(other.raw_ptr_);
            other.raw_ptr_ = nullptr;
        }
        return *this;
    }

    // Создаёт в куче массив из size элементов типа Type.
    // Если size == 0, поле raw_ptr_ должно быть равно nullptr
    explicit ArrayPtr(size_t size) {
        if (size == 0) {
            raw_ptr_ = nullptr;
        }
        else {
       raw_ptr_ = new Type[size];
        }
      
    }

    // Конструктор из сырого указателя, хранящего адрес массива в куче либо nullptr
    explicit ArrayPtr(Type* raw_ptr) noexcept {
        raw_ptr_ = raw_ptr;
    }

    // Запрещаем копирование
    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr() {
       delete [] raw_ptr_;
    }

    // Запрещаем присваивание
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    // Прекращает владением массивом в памяти, возвращает значение адреса массива
    // После вызова метода указатель на массив должен обнулиться
    [[nodiscard]] Type* Release() noexcept {
        Type *temp_arr = raw_ptr_;
        raw_ptr_ = nullptr;
        return temp_arr;
    }

    // Возвращает ссылку на элемент массива с индексом index
    Type& operator[](size_t index) noexcept {
        Type* temp =  &raw_ptr_[index];
        Type& result = *temp;
        return result;
    }

    // Возвращает константную ссылку на элемент массива с индексом index
    const Type& operator[](size_t index) const noexcept {
       Type* temp =  &raw_ptr_[index];
       const Type& result = *temp;
       return result;
    }

    // Возвращает true, если указатель ненулевой, и false в противном случае
    explicit operator bool() const {
        if (raw_ptr_) {
            return true;
        }
        else {
            return false;
    }
    }
    // Возвращает значение сырого указателя, хранящего адрес начала массива
    Type* Get() const noexcept {
        return raw_ptr_;
    }

    // Обменивается значениям указателя на массив с объектом other
    void swap(ArrayPtr& other) noexcept {
        std::swap(raw_ptr_,other.raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};
