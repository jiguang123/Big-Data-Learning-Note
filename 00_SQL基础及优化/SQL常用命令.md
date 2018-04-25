## SQL常用命令

	[SQl命令在线练习] (https://sqlbolt.com/lesson/introduction)

---
#### 1、SELECT column, another_column, … FROM mytable;

    	SELECT title FROM movies;

	 	SELECT director FROM movies;

	 	SELECT title, director FROM movies;

		SELECT * FROM movies;

---
#### 2、SELECT column, another_column, … FROM mytable WHERE condition AND/OR another_condition AND/OR …;

    	SELECT id, title FROM movies WHERE id = 6;

   		SELECT title, year FROM movies WHERE year BETWEEN 2000 AND 2010;

   		SELECT title, year FROM movies WHERE year < 2000 OR year > 2010;

   		SELECT title, year FROM movies WHERE year <= 2003;

   		SELECT title, director FROM movies WHERE title LIKE "Toy Story%";

   		SELECT title, director FROM movies WHERE director = "John Lasseter";

   		SELECT title, director FROM movies WHERE director != "John Lasseter";

   		SELECT * FROM movies WHERE title LIKE "WALL-_";

   		SELECT city, population FROM north_american_cities WHERE country = "Canada";


---
#### 3、SELECT DISTINCT column, another_column, … FROM mytable WHERE condition(s);

    	SELECT DISTINCT director FROM movies ORDER BY director ASC;

   		SELECT city, latitude FROM north_american_cities WHERE country = "United States" ORDER BY latitude DESC;

   		SELECT city, longitude FROM north_american_cities WHERE longitude < -87.629798 ORDER BY longitude ASC;


---
#### 4、SELECT column, another_column, … FROM mytable WHERE condition(s) ORDER BY column ASC/DESC LIMIT num_limit OFFSET num_offset;

   		SELECT title, year FROM movies ORDER BY year DESC LIMIT 4;

   		SELECT title FROM movies ORDER BY title ASC LIMIT 5;

   		SELECT title FROM movies ORDER BY title ASC LIMIT 5 OFFSET 5;

   		SELECT city, population FROM north_american_cities WHERE country LIKE "Mexico" ORDER BY population DESC LIMIT 2;

   		SELECT city, population FROM north_american_cities WHERE country LIKE "United States" ORDER BY population DESC LIMIT 2 OFFSET 2;

---
#### 5、SELECT column, another_table_column, … FROM mytable INNER JOIN another_table ON mytable.id = another_table.id WHERE condition(s) ORDER BY column, … ASC/DESC LIMIT num_limit OFFSET num_offset;

   		SELECT title, domestic_sales, international_sales 
   		 FROM movies 
    		JOIN boxoffice
    	 		ON movies.id = boxoffice.movie_id;

    	SELECT title, domestic_sales, international_sales
		 FROM movies
			 JOIN boxoffice
			    ON movies.id = boxoffice.movie_id
		WHERE international_sales > domestic_sales;

		SELECT title, rating
		FROM movies
			  JOIN boxoffice
			    ON movies.id = boxoffice.movie_id
		ORDER BY rating DESC;


---
#### 6、SELECT column, another_column, … FROM mytable INNER/LEFT/RIGHT/FULL JOIN another_table ON mytable.id = another_table.matching_id WHERE condition(s) ORDER BY column, … ASC/DESC LIMIT num_limit OFFSET num_offset;

   		SELECT DISTINCT building_name, role 
		  FROM buildings 
			  LEFT JOIN employees
			    ON building_name = building;

#### 7、SELECT AGG_FUNC(column_or_expression) AS aggregate_description, … FROM mytable WHERE constraint_expression GROUP BY column;	

   		SELECT MAX(years_employed) as Max_years_employed FROM employees;

   		SELECT role, AVG(years_employed) as Average_years_employed
		FROM employees
		GROUP BY role;

		SELECT building, SUM(years_employed) as Total_years_employed
		FROM employees
		GROUP BY building;

---
#### 8、SELECT DISTINCT column, AGG_FUNC(column_or_expression), … FROM mytable JOIN another_table ON mytable.column = another_table.column WHERE constraint_expression GROUP BY column HAVING constraint_expression ORDER BY column ASC/DESC LIMIT count OFFSET COUNT;	

    	SELECT director, SUM(domestic_sales + international_sales) as Cumulative_sales_from_all_movies
		FROM movies
		       INNER JOIN boxoffice
			         ON movies.id = boxoffice.movie_id
		GROUP BY director;	 


---
#### 9、UPDATE mytable SET column = value_or_expr, other_column = another_value_or_expr, … WHERE condition;

    	UPDATE movies SET title = "Toy Story 3", director = "Lee Unkrich" WHERE id = 11;


---
#### 10、DELETE FROM mytable WHERE condition;

		DELETE FROM movies where director = "Andrew Stanton";


   		
---
#### 11、CREATE TABLE IF NOT EXISTS mytable (	column DataType TableConstraint DEFAULT default_value,   another_column DataType TableConstraint DEFAULT default_value, … );


		CREATE TABLE movies (
			    id INTEGER PRIMARY KEY,
			    title TEXT,
			    director TEXT,
			    year INTEGER, 
			    length_minutes INTEGER
		);










