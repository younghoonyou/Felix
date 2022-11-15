import React, { useState } from 'react';
import axios from 'axios';
import '../App.css';
import InputName from '../components/InputName';
import NumberBox from '../components/NumberBox';
import ConfirmButton from '../components/ConfirmButton';
import Amount from '../components/Amount';
import Balance from '../components/Balance';

const LandingPage = () => {
  const [user, setUser] = useState('');
  const [restaurant, setRestaurant] = useState('');
  const [amount, setAmount] = useState('');
  const config = {
    headers: {
      'Content-Type': 'application/json',
    },
  };
  const handlePost = async () => {
    await axios.post(
      'http://127.0.0.1:8000',
      { user, restaurant, amount },
      config
    );
  };
  const handleSubmit = async (e) => {
    e.preventDefault();
    handlePost();
  };

  const changeAmount = (e) => {
    setAmount(e.target.value);
  };

  const deleteAmount = () => {
    setAmount('');
  };

  return (
    <div className='rectangle-box'>
      <form className='form-box' onSubmit={handleSubmit}>
        <InputName
          title='User'
          value={user}
          onChange={(e) => setUser(e.target.value)}
          pre={'User Name'}
        />
        <InputName
          title='Restaurant'
          value={restaurant}
          onChange={(e) => setRestaurant(e.target.value)}
          pre={'Restaurant Name'}
        />
        <Amount
          amount={amount}
          onChange={changeAmount}
          onClick={deleteAmount}
        />
        <NumberBox amount={setAmount} total={amount} />
        <ConfirmButton title='Confirm amount' />
      </form>
      <Balance />
    </div>
  );
};

export default LandingPage;
