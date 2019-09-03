-- Q2
create table Product (
	model int not null,
	manufacturer char(20),
	retail int not null,
	instock int not null,
	relaeseDate char(8), -- ex - 07/17/18
	primary key (model)
);

create table Camera (
	model int not null,
	pixel int not null,
	focalRange int,
	apetureRange int,
	electronicVF bool,
	opticalVF bool,
	TTLopticalVF bool,
	opticalRF bool,
	check (
		(opticalVF = false and TTLopticalVF = false and opticalRF = false) or 
		(opticalVF = true and TTLopticalVF = false and opticalRF = false) or
		(opticalVF = false and TTLopticalVF = true and opticalRF = false) or
		(opticalVF = false and TTLopticalVF = false and opticalRF = true)
	),
	foreign key (model) references Product(model)	
);

create table Lens (
	model int not null,
    focalRange int,
    apetureRange int,
	prime bool,
    foreign key (model) references Product(model)
);

create table Customer (
	id int not null,
	name char(20),
	email char(20),
	address char(30),
	primary key(id)
);

create table Purchase (
	model int not null,
	id int not null,
    sellingPrice int not null,
    outstanding bool,
    foreign key (model) references Product(model),
	foreign key (id) references Customer(id),
);

create table Evaluation (
    model int not null,
    id int not null,
    score int not null,
	customerComment char[100],
    check (score <= 5 and score >= 1),
	foreign key (model) references Product(model),
    foreign key (id) references Customer(id),
);
