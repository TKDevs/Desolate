#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
//-----------------------------------------------------------------------------------
//Point class
class Point {
public:
	Point(float x, float y): x_(x), y_(y){}

	//get functions
	float getX() { return x_; }
	float getY() { return y_; }
private:
	float x_;
	float y_;
};
//-----------------------------------------------------------------------------------
//Rectangle class
class Rectangle {
public:
	Rectangle(float x, float y, float width, float height): x_(x), y_(y), width_(width), height_(height){}

	//returns a boolean if the point is in the rectangle or not
	bool contains(Point* point) {
		return (point->getX() > x_ &&
				point->getX() < x_ + width_ &&
				point->getY() > y_ &&
				point->getY() < y_ + height_);
	}

	//returns a boolean if two rectangle intersect or not
	bool intersects(Rectangle* area) {
		return !(area->getX() > x_ + width_ ||
				area->getX() + area->getWidth() < x_ ||
				area->getY() > y_ + height_ ||
				area->getY() + area->getHeight() < y_);
	}

	//get functions
	float getX() { return x_; }
	float getY() { return y_; }
	float getWidth() { return width_; }
	float getHeight() { return height_; }
private:
	float x_;
	float y_;
	float width_;
	float height_;
};
//-----------------------------------------------------------------------------------
//Quadtree class
class Quadtree {
public:
	Quadtree(Rectangle boundary, int capacity):boundary_(boundary), capacity_(capacity){}

	//insert a point into the quadtree
	void insert(Point* point) {
		if (!boundary_.contains(point)) { return; }
		else {
			if (points_.size() < capacity_) { points_.push_back(point); }
			else {
				if (!divided_) { subdivide(); }
				top_left_->insert(point);
				top_right_->insert(point);
				bottom_left_->insert(point);
				bottom_right_->insert(point);
			}
		}
	}

	//query a specific area in the quadtree
	std::vector<Point*> query(Rectangle* area) {
		std::vector<Point*> found;
		if (!boundary_.intersects(area)) { return found; }
		else {
			for (Point* p : points_) {
				if (area->contains(p)) { found.push_back(p); }
			}
			if (divided_) {
				top_left_->querySubsections(area, &found);
				top_right_->querySubsections(area, &found);
				bottom_left_->querySubsections(area, &found);
				bottom_right_->querySubsections(area, &found);
			}
			return found;
		}
	}

	//consol log the points
	void consolLog() {
		std::cout << "new Quadtree:" << std::endl;
		if (points_.size() == 0) { std::cout << "Empty" << '\n' << std::endl; }
		else {
			for (Point* p : points_) { std::cout << "Point " << " X Position:" << p->getX() << "    Y Position:" << p->getY() << std::endl; }
			std::cout << '\n';
			if (divided_) {
				top_left_->consolLog();
				top_right_->consolLog();
				bottom_left_->consolLog();
				bottom_right_->consolLog();
			}
		}
	}

	//shows the grid of the quadtree
	void show(sf::RenderWindow* window) {
		sf::RectangleShape rect(sf::Vector2f(boundary_.getWidth(), boundary_.getHeight()));
		rect.setPosition(boundary_.getX(), boundary_.getY());
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color(255, 255, 255));
		rect.setFillColor(sf::Color(0, 0, 0));
		window->draw(rect);

		if (divided_) {
			top_left_->show(window);
			top_right_->show(window);
			bottom_left_->show(window);
			bottom_right_->show(window);
		}
	}

private:
	//subdividign the quadtree in 4 different quadtrees
	void subdivide() {
		divided_ = true;
		top_left_ = new Quadtree(Rectangle(boundary_.getX(), boundary_.getY(), boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
		top_right_ = new Quadtree(Rectangle(boundary_.getX() + boundary_.getWidth() / 2, boundary_.getY(), boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
		bottom_left_ = new Quadtree(Rectangle(boundary_.getX(), boundary_.getY() + boundary_.getWidth() / 2, boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
		bottom_right_ = new Quadtree(Rectangle(boundary_.getX() + boundary_.getWidth() / 2, boundary_.getY() + boundary_.getHeight() / 2, boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
	}
	//query for subsection 
	//new function for better memory management (passing pointers instead and not returning a value)
	void querySubsections(Rectangle* area, std::vector<Point*>* found) {
		if (!boundary_.intersects(area)) { return ; }
		else {
			for (Point* p : points_) {
				if (area->contains(p)) { found->push_back(p); }
			}
			if (divided_) {
				top_left_->querySubsections(area, found);
				top_right_->querySubsections(area, found);
				bottom_left_->querySubsections(area, found);
				bottom_right_->querySubsections(area, found);
			}
			return ;
		}
	}

	Rectangle boundary_;
	int capacity_;
	bool divided_;
	std::vector<Point*> points_;
	Quadtree* top_left_;
	Quadtree* top_right_;
	Quadtree* bottom_left_;
	Quadtree* bottom_right_;
};
#endif