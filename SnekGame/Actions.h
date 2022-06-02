#pragma once

struct Action {
	float m_straight;
	float m_right;
	float m_left;

	Action(float weight) {
		m_straight = weight;
		m_right = weight;
		m_left = weight;
	}

	float greatest() {
		float turn = (m_left > m_right) ? m_left : m_right;
		float greatest = (m_straight > turn) ? m_straight : turn;

		return greatest;
	}

	int best() {
		int turn = (m_left > m_right) ? 2 : 1;
		int best = (m_straight >= turn) ? 0 : turn;

		return best;
	}

	void add(int index, float amount) {
		switch (index) {
		case 0: 
			m_straight += amount;
			break;
		case 1:
			m_right += amount;
			break;
		case 2:
			m_left += amount;
			break;
		default:
			return;
		}
	}

	float get(int index) {
		float val = -1;
		switch (index)
		{
		case 0:
			val = m_straight;
		case 1:
			val = m_right;
		case 2:
			val = m_left;
		default:
			break;
		}

		return val;
	}
};