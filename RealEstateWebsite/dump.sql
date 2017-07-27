use rdiersin_realestate;


create table Testimonial (
	TestimonialTimestamp datetime(6) primary key not null,
    FinalRating int(2) not null,
    DateAndUsername varchar(100) not null,
    Description varchar(500) not null,
    LocalKnowledgeRating int (2) not null,
    ProcessExpertiseRating int (2) not null,
    ResponsivenessRating int (2) not null,
    NegotiationSkillsRating int (2) not null,
    Review varchar(2000) not null
);

create table Property (
	PropertyTimestamp datetime(6) primary key not null,
    Address varchar (100) not null,
    Description varchar(2000) not null,
    ImgLink varchar(1000) not null,
    ZillowLink varchar(1000) not null
);

create table Blog (
	BlogTimestamp datetime(6) primary key not null,
    Title varchar(100) not null,
    Image varchar(500),
    ImageCaption varchar(1000),
    SubTitle varchar(100),
    BlogEntry varchar(2000)
);