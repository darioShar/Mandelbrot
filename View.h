#pragma once

	struct Vue {
		double xmin = -1.0f;
		double xmax = 1.0f;
		double ymin = -1.0f;
		double ymax = 1.0f;

		// adapts to the screen apsect ratio so that plane doesn't look distorted.
		Vue(double aspectRatio = 1.0f) {
			double middle = (xmax + xmin) / 2.0f;
			double dx = middle - xmin;
			dx *= aspectRatio;
			xmin = middle - dx;
			xmax = middle + dx;
		}

		void operator=(Vue const & nview) {
			xmin = nview.xmin;
			xmax = nview.xmax;
			ymin = nview.ymin;
			ymax = nview.ymax;
		}

		void zoom(double factor) {
			double middle = (xmax + xmin) / 2.0f;
			double dx = middle - xmin;
			dx /= factor;
			xmin = middle - dx;
			xmax = middle + dx;

			middle = (ymax + ymin) / 2.0f;
			double dy = middle - ymin;
			dy /= factor;
			ymin = middle - dy;
			ymax = middle + dy;
		}

		void move(double x, double y) {
			xmin += x;
			xmax += x;
			ymin += y;
			ymax += y;
		}

	};
