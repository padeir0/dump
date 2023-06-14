func Control() {
	res := makeResource()
	Use(res)
	Close(res)
}

func Use(res *Resource) {
	// ...
	failed := FallibleOperation(res)
	if failed {
		return
	}
	// ...
}

func DeFEr() {
	res := makeResource()
	defer Close(res)
	// ...
	failed := FallibleOperation(res)
	if failed {
		return
	}
	// ...
}
