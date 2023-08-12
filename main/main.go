package main

import (
	"fmt"
	"sync"
)

type People struct {
	name  string
	say   string
	money int
}
type Money struct {
	mu    sync.Mutex
	value int
}

func main() {
	var wg sync.WaitGroup
	allWorlds := []string{}
	allMoney := Money{mu: sync.Mutex{}, value: 0}
	person1 := People{name: "b1", say: "Hello", money: 100}
	person2 := People{name: "b2", say: "World", money: 200}
	person3Ptr := &People{name: "b3", say: "!", money: 300}
	wg.Add(3)
	go speak(&person1, &allWorlds, &allMoney, &wg)
	go speak(&person2, &allWorlds, &allMoney, &wg)
	go speak(person3Ptr, &allWorlds, &allMoney, &wg)
	wg.Wait()
	fmt.Println("last word was :", allWorlds)
	fmt.Println("all money was :", allMoney.value)
}

func speak(person *People, allWorlds *[]string, allMoney *Money, wg *sync.WaitGroup) {
	defer wg.Done()
	allMoney.mu.Lock()
	defer allMoney.mu.Unlock()
	fmt.Printf("%s says: %s\n", person.name, person.say)
	*allWorlds = append(*allWorlds, person.say)
	allMoney.value += person.money
}
