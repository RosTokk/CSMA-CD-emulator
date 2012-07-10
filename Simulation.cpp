#include "Simulation.h"

#include <vector>

#include "Environment.h"
#include "Clock.h"
#include "Computer.h"
#include "Events.h"
#include "PriorityQueue.h"

using std::vector;

unsigned long long Clock::time_ = 0;

Simulation::Simulation(unsigned number_computers, double lan_speed, int packet_length)
    : number_computers_(number_computers)
    , lan_speed_(lan_speed)
    , packet_length_(packet_length) {
  Run();
}

void Simulation::Run() {
  bool ended = false;
  Clock::SetTime(0);

  PriorityQueue events;
  vector<Computer> computers;

  for (int i = 0; i < number_computers_; i++) {
    computers.push_back(Computer(&events, COMP_DISTANCE * (i + 1)));
    events.Insert(new ArrivalEvent(&computers[i]));
  }

  for (int i = 0; i < 10; i++) {
    Event* event = events.Remove();
    event->HandleEvent();
    delete event;
  }
}

