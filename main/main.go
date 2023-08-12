package main

import (
	"fmt"
	"sync"
)

type People struct {
	name string
	say  string
}

func main() {
	var wg sync.WaitGroup
	var mu sync.Mutex
	allWorlds := ""

	person1 := People{name: "b1", say: "Hello"}
	person2 := People{name: "b2", say: "World"}
	person3Ptr := new(People)
	person3Ptr.name = "b3"
	person3Ptr.say = "!"

	wg.Add(3)

	go speak(&person1, &mu, &allWorlds, &wg)
	go speak(&person2, &mu, &allWorlds, &wg)
	go speak(person3Ptr, &mu, &allWorlds, &wg)

	wg.Wait()
	fmt.Println("last word was :", allWorlds)
}

func speak(person *People, mu *sync.Mutex, allWorlds *string, wg *sync.WaitGroup) {
	defer wg.Done()
	mu.Lock()
	defer mu.Unlock()

	fmt.Printf("%s says: %s\n", person.name, person.say)
	*allWorlds = *allWorlds + " " + person.say
}
