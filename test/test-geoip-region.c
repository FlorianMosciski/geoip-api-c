/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* test-geoip-region.c
 *
 * Copyright (C) 2002 MaxMind.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <GeoIP.h>

int main () {
	GeoIP * gi;
	GeoIPRegion * gir;

  FILE *f;
  char ipAddress[30];
  char expectedCountry[3];
  char expectedCountry3[4];

	gi = GeoIP_open("../data/GeoIPRegion.dat", GEOIP_MEMORY_CACHE);

	if (gi == NULL) {
		fprintf(stderr, "Error opening database\n");
		exit(1);
	}

  f = fopen("region_test.txt","r");

	if (f == NULL) {
		fprintf(stderr, "Error opening region_test.txt\n");
		exit(1);
	}

  while (fscanf(f, "%s", ipAddress) != EOF) {
    fscanf(f, "%s", expectedCountry);
    fscanf(f, "%s", expectedCountry3);

		printf("ip = %s\n",ipAddress);

		gir = GeoIP_region_by_name (gi, ipAddress);

		if (gir != NULL) {
			printf("%s, %s\n",
						 gir->country_code,
						 gir->region);

			GeoIPRegion_delete(gir);
		} else
			printf("NULL!\n");
	}

	GeoIP_delete(gi);
	return 0;
}