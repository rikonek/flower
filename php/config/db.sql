SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

CREATE TABLE `measurement` (
  `id` int(10) UNSIGNED NOT NULL,
  `date` datetime NOT NULL,
  `ground_humidity` tinyint(3) UNSIGNED NOT NULL,
  `ambient_humidity` tinyint(3) UNSIGNED NOT NULL,
  `ambient_temperature` float(5,2) NOT NULL,
  `water_level` tinyint(1) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

ALTER TABLE `measurement`
  ADD PRIMARY KEY (`id`),
  ADD KEY `date` (`date`);

ALTER TABLE `measurement`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;