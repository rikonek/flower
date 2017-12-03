-- phpMyAdmin SQL Dump
-- version 4.6.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 03, 2017 at 07:59 AM
-- Server version: 5.7.14
-- PHP Version: 5.6.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `flower`
--

-- --------------------------------------------------------

--
-- Table structure for table `measurement`
--

CREATE TABLE `measurement` (
  `id` int(10) UNSIGNED NOT NULL,
  `id_plant` int(10) UNSIGNED NOT NULL,
  `date` datetime NOT NULL,
  `ground_humidity` tinyint(3) UNSIGNED NOT NULL,
  `ambient_humidity` tinyint(3) UNSIGNED NOT NULL,
  `ambient_temperature` float(5,1) NOT NULL,
  `water_level` tinyint(1) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `measurement`
--
ALTER TABLE `measurement`
  ADD PRIMARY KEY (`id`),
  ADD KEY `date` (`date`),
  ADD KEY `id_plant` (`id_plant`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `measurement`
--
ALTER TABLE `measurement`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `measurement`
--
ALTER TABLE `measurement`
  ADD CONSTRAINT `measurement_ibfk_1` FOREIGN KEY (`id_plant`) REFERENCES `plant` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
